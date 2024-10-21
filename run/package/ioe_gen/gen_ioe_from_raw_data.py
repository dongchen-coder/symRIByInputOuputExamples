import os
import pandas as pd
import math
import itertools
from random import sample

def init_ioe_paths(path, bench):
    os.system("mkdir -p " + path + "/" + bench)   
    os.system("rm -rf " + path + "/" + bench + "/src_only")
    os.system("rm -rf " + path + "/" + bench + "/src_snk")
    os.system("rm -rf " + path + "/" + bench + "/src_snk_plus")
    os.system("rm -rf " + path + "/" + bench + "/ibound")
    os.system("mkdir -p " + path + "/" + bench + "/src_only")
    os.system("mkdir -p " + path + "/" + bench + "/src_snk")
    os.system("mkdir -p " + path + "/" + bench + "/src_snk_plus")
    os.system("mkdir -p " + path + "/" + bench + "/ibound")
    return

def dataframe_to_input_output_examples(bench, cache_config, df, bound_values, spec):
    if (spec == 'src_only'):
        src_id = str(df.iloc[0]['source reference ID'])
        snk_id = str(df.iloc[0]['sink reference ID'])
        src_iv = df.iloc[0]['source iteration vector'].split()
        src_iv_ = df.iloc[0]['source iteration vector'].replace(' ', '_')
        f = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+src_id+'_isrc_'+src_iv_+'.ri.'+cache_config,'w')
        for bound_value in bound_values:
            row = df.loc[df['bound values'] == bound_value]
            bound_value = bound_value.split()
            output = str(0)
            if (len(row) != 0):
                output = str(row['reuse interval'].values[0])
                
            entry = ''
            for idx in range(len(src_iv)):
                entry += 'isrc'+str(idx)+' '+src_iv[idx]+' '
            for idx in range(len(bound_value)):
                entry += 'b'+str(idx)+' '+bound_value[idx]+' '
            entry+= '_out ' + output + '\n'
            f.write(entry)
        f.close()
    if (spec == 'src_snk'):
        src_id = str(df.iloc[0]['source reference ID'])
        snk_id = str(df.iloc[0]['sink reference ID'])
        src_iv = df.iloc[0]['source iteration vector'].split()
        src_iv_ = df.iloc[0]['source iteration vector'].replace(' ', '_')
        f = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+src_id+'_isrc_'+src_iv_+'_refsnk_'+snk_id+'.ri.'+cache_config,'w')
        for bound_value in bound_values:
            row = df.loc[df['bound values'] == bound_value]
            bound_value = bound_value.split()
            output = str(0)
            if (len(row) != 0):
                output = str(row['reuse interval'].values[0])
                
            entry = ''
            for idx in range(len(src_iv)):
                entry += 'isrc'+str(idx)+' '+src_iv[idx]+' '
            for idx in range(len(bound_value)):
                entry += 'b'+str(idx)+' '+bound_value[idx]+' '
            entry+= '_out ' + output + '\n'
            f.write(entry)
        f.close()
    if (spec == 'src_snk_plus'):
        src_id = str(df.iloc[0]['source reference ID'])
        snk_id = str(df.iloc[0]['sink reference ID'])
        src_iv = df.iloc[0]['source iteration vector'].split()
        src_iv_ = df.iloc[0]['source iteration vector'].replace(' ', '_')
        f = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+src_id+'_isrc_'+src_iv_+'_refsnk_'+snk_id+'.ri.'+cache_config,'w')
        for bound_value in bound_values:
            row = df.loc[df['bound values'] == bound_value]
            bound_value = bound_value.split()

            snk_iv = ['0'] * len(df.iloc[0]['sink iteration vector'].split())            
            output = str(0)
            if (len(row) != 0):
                snk_iv = row['sink iteration vector'].values[0].split()
                output = str(row['reuse interval'].values[0])

            entry = ''
            for idx in range(len(src_iv)):
                entry += 'isrc'+str(idx)+' '+src_iv[idx]+' '
            for idx in range(len(snk_iv)):
                entry += 'isnk'+str(idx)+' '+snk_iv[idx]+' '
            for idx in range(len(bound_value)):
                entry += 'b'+str(idx)+' '+bound_value[idx]+' '
            entry+= '_out ' + output + '\n'
            f.write(entry)
        f.close()
        
        snk_iv_len = len(df.iloc[0]['sink iteration vector'].split())
        for snk_iv_idx in range(snk_iv_len):
            f = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+src_id+'_isrc_'+src_iv_+'_refsnk_'+snk_id+'.isnk'+str(snk_iv_idx)+'.'+cache_config,'w')
            entry = ''
            for idx in range(len(src_iv)):
                entry += 'isrc'+str(idx)+' '+src_iv[idx]+' '
            for idx in range(len(bound_value)):
                entry += 'b'+str(idx)+' '+bound_value[idx]+' '
            entry+= '_out ' + snk_iv[snk_iv_idx] + '\n'           
            f.close()


    if (spec == 'ibound'):
        src_ref_id = df['source reference ID'][0]
        num_of_nested_loops = len(df['iteration vector'][0].strip().split(' '))
        loop_name = ['loop ' + str(x) for x in range(num_of_nested_loops)]
        if (num_of_nested_loops <= 1):
            df['loop 0'] = df['iteration vector']
        else:
            df[loop_name] = df['iteration vector'].str.split(' ', n=num_of_nested_loops-1, expand=True)
        
        for i in range(num_of_nested_loops):
            df['loop ' + str(i)] = df['loop ' + str(i)].astype(int)
        
        for i in range(num_of_nested_loops):
            fmin = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+str(src_ref_id)+'.imin'+str(i)+'.ibound', 'w')
            fmax = open('../data/input-output_examples/'+bench+'/'+spec+'/'+bench+'_refsrc_'+str(src_ref_id)+'.imax'+str(i)+'.ibound', 'w')
            for bound_value in bound_values:
                df_bound = df.loc[df['bound values'] == bound_value]
                bound_value = bound_value.split()
                entry = ''
                for idx in range(len(bound_value)):
                    entry += 'b'+str(idx)+' '+bound_value[idx]+' '
                fmin.write(entry+'_out '+str(df_bound['loop '+str(i)].min())+'\n')
                fmax.write(entry+'_out '+str(df_bound['loop '+str(i)].max())+'\n')
            fmin.close()
            fmax.close()
        
def gen_ioe_from_raw_csv_data(bench, paras, cache_config, sampling_rate = 0.2, max_sampling_number = 20):
    # merge all reuse interval csv files with different train sizes
    print("Reading raw data *",)
    raw_data_path = "../data/raw_data/"+cache_config+"/"+bench
    fileList = os.listdir(raw_data_path)
    li = []
    for file_name in fileList:
        file_name_with_path = raw_data_path + "/" + file_name
        df = pd.read_csv(file_name_with_path, index_col=False, header = 0, lineterminator='\n', sep=',', on_bad_lines='error')
        df['bound values'] = " ".join(file_name.replace('.csv','').split('_')[1:])
        li.append(df)
    df = pd.concat(li, axis=0, ignore_index=True)

    # sample source iteration vectors
    number_of_unique_src_ivs = len(df.groupby(['source reference ID', 'source iteration vector']).size().reset_index().rename(columns={0:"count"}))
    sampling_rate = min(sampling_rate, float(max_sampling_number) / number_of_unique_src_ivs)

    # generate inpout-output examples
    print(f"Sample source I {number_of_unique_src_ivs} with rate {sampling_rate}. Gen IOE for RI *",)
    src_ref_ids = df['source reference ID'].unique().tolist()
    for src_ref_id in src_ref_ids:
        df_src = df.loc[df['source reference ID'] == src_ref_id]   
        
        # input-output examples for source only
        src_ivs = df_src['source iteration vector'].unique().tolist()
        src_ivs_sampled = sample(src_ivs, int(math.ceil(len(src_ivs) * sampling_rate)))
        for src_iv in src_ivs_sampled:
            df_src_ivs = df_src.loc[df['source iteration vector'] == src_iv]
            bound_values = df_src_ivs['bound values']
            dataframe_to_input_output_examples(bench, cache_config, df_src_ivs, bound_values, 'src_only')
        
        # input-output examples for source sink (+)
        sink_ref_ids = df_src['sink reference ID'].unique().tolist()
        for sink_ref_id in sink_ref_ids:
            df_src_snk = df_src.loc[df['sink reference ID'] == sink_ref_id]
            src_ivs = df_src_snk['source iteration vector'].unique().tolist()
            for src_iv in set(src_ivs) & set(src_ivs_sampled):
                df_src_snk_ivs = df_src_snk.loc[df['source iteration vector'] == src_iv]
                bound_values = df_src_snk_ivs['bound values']
                #print(df_src_snk_ivs)
                dataframe_to_input_output_examples(bench, cache_config, df_src_snk_ivs, bound_values, 'src_snk')
                dataframe_to_input_output_examples(bench, cache_config, df_src_snk_ivs, bound_values, 'src_snk_plus')

    # merge all loop induction variable csv files with different train sizes
    print("Gen IOE for Bounds *",)
    raw_data_path = "../data/raw_data/ibound/"+bench
    li = []
    for file_name in os.listdir(raw_data_path):
        file_name_with_path = raw_data_path + "/" + file_name
        df = pd.read_csv(file_name_with_path, index_col = None, header = 0)
        df['bound values'] = " ".join(file_name.replace('.csv','').split('_')[1:])
        li.append(df)
    df = pd.concat(li, axis=0, ignore_index=True)
    
    for src_ref_id in src_ref_ids:
        df_src = df.loc[df['source reference ID'] == src_ref_id].copy().reset_index()
        dataframe_to_input_output_examples(bench, cache_config, df_src, bound_values, 'ibound')

    print("Finished")
