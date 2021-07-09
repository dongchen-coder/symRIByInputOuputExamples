/* Copyright 2008, 2010, Oracle and/or its affiliates.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

There are special exceptions to the terms and conditions of the GPL
as it is applied to this software. View the full text of the
exception in file EXCEPTIONS-CONNECTOR-C++ in the directory of this
software distribution.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

vector<string> split_string(string input_str, char split_ch) {
    vector<string> output_str;
    string tmp = "";
    for (auto ch : input_str) {
        if(ch == split_ch) {
            if (tmp != "") {
                output_str.push_back(tmp);
            }
            tmp = "";
        } else {
            tmp.push_back(ch);
        }
    }
    if (tmp != "") {
        output_str.push_back(tmp);
    }
    return output_str;
}

void read_data_into_DB(string bench_name, string path, sql::Statement *stmt) {
    
    string bounds;
    string addr;
    string ref_src;
    string iter_src;
    string pos_src;
    string ref_snk;
    string iter_snk;
    string pos_snk;
    string cls;
    string ds;
    string ri;
    for (const auto & entry : std::experimental::filesystem::recursive_directory_iterator(path)) {
        string path_str = entry.path().string();
        if (path_str.find(".txt") != std::string::npos && path_str.find(bench_name) != std::string::npos) {
            string line;
            ifstream raw_file;
            raw_file.open(path_str, ios::in);
          
            string file_str = path_str.substr(path_str.rfind('/')+1);
            file_str = file_str.substr(0, file_str.size() - 4);
            cout << file_str << endl;
            bench_name = file_str.substr(0, file_str.find('_'));
            bounds = file_str.substr(file_str.find('_')+1);
            
            while ( getline(raw_file, line) ) {
                vector<string> line_list = split_string(line, ',');
                addr = line_list[0];
                vector<string> ref_iter_src = split_string(line_list[1], ' ');
                ref_src = ref_iter_src[0];
                iter_src = "";
                for (int i = 1; i < ref_iter_src.size(); i++) iter_src += ref_iter_src[i] + "_";
                iter_src.pop_back();
                vector<string> ref_iter_snk = split_string(line_list[2], ' ');
                ref_snk = ref_iter_snk[0];
                iter_snk = "";
                for (int i = 1; i < ref_iter_snk.size(); i++) iter_snk += ref_iter_snk[i] + "_";
                iter_snk.pop_back();
                pos_src = line_list[3];
                pos_snk = line_list[4];
                cls = line_list[5];
                ds = line_list[6];
                ri = line_list[7];
                
                stmt->execute("INSERT INTO all_meta_data(bench, bound, addr, ref_src, iter_src, pos_src, ref_snk, iter_snk, pos_snk, cls, ds, ri) VALUES ('" + bench_name +  "', '" + bounds +  "', '" + addr +  "', '" + ref_src +  "', '" + iter_src +  "', '" + pos_src +  "', '" + ref_snk +  "', '" + iter_snk +  "', '" + pos_snk +  "', '" + cls +  "', '" + ds +  "', '" + ri + "')");
            }
            raw_file.close();
        }
    }
}

void construct_input_output_example(sql::Statement *stmt) {
    vector<string> iter_src_v;
    vector<string> ref_src_v;
    
    sql::ResultSet *res;
    
    /* get all sampled source iterations */
    res = stmt->executeQuery("select distinct iter_src from all_meta_data");
    while (res->next()) {
        if (res->getString("iter_src") != "") { iter_src_v.push_back(res->getString("iter_src")); }
    }
    
    /* get all source references */
    res = stmt->executeQuery("select distinct ref_src from all_meta_data");
    while(res->next()) {
        if (res->getString("ref_src") != "") { ref_src_v.push_back(res->getString("ref_src")); }
    }
    
    /* group by srouce iteration */
    for (auto ref_src : ref_src_v) {
        for (auto iter_src : iter_src_v) {
            cout << "grouped" << endl;
            res = stmt->executeQuery("select * from all_meta_data where iter_src = '" + iter_src + "' and ref_src = '" + ref_src + "'");
            string bounds;
            string ri;
            while (res->next()) {
                bounds = res->getString("bound");
                ri = res->getString("ri");
                cout << bounds << " " << ri << endl;
            }
        }
    }
}

int main(void)
{

try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
  
    /* read all data */
    stmt = con->createStatement();
    stmt->execute("CREATE DATABASE IF NOT EXISTS reuse_interval_meta");
    
    /* Connect to the MySQL  database */
    con->setSchema("reuse_interval_meta");
    stmt->execute("USE reuse_interval_meta");

    stmt->execute("DROP TABLE IF EXISTS all_meta_data");
    stmt->execute("CREATE TABLE all_meta_data(bench varchar(50), bound varchar(50), addr int, ref_src int, iter_src varchar(50), pos_src int, ref_snk int, iter_snk varchar(50), pos_snk int, cls int, ds int, ri int)");

    string path = "../raw_ris_per_size_ELM/";
    read_data_into_DB("stencil", path, stmt);
    construct_input_output_example(stmt);
  
    delete stmt;
    delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}
