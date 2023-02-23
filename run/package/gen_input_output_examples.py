import sys
import os
import pandas as pd
from gen_raw_data import *
from gen_ioe_from_raw_data import *
from sample_raw_data import *
from paths import *

def get_one_dataframe_for_all_params(bench, parms, cache_config, file_type):
    li = []
    for parm in parms:
        parm_str_underline = get_parms_str_underline(parm)
        file_name = raw_data_path + cache_config + "/" + bench + "/" + bench + "_" + parm_str_underline + "." + file_type
        df = pd.read_csv(file_name, index_col=False, header=0, lineterminator='\n', sep=',', error_bad_lines=False)
        df['bound values'] = get_parms_str_space(parm)  # parm_str_underline.replace('_', ' ')
        li.append(df)
    df = pd.concat(li, axis=0, ignore_index=True)
    return df

def get_iter_vecs(bench, parms_train, df):
    iter_vecs = {}
    src_ids = set(list(df['source reference ID']))
    snk_ids = set(list(df['sink reference ID']))
    for src_id in src_ids:
        df_src = df.loc[df['source reference ID'] == src_id]
        iter_vecs[src_id] = list(df_src['source iteration vector'])
        for snk_id in snk_ids:
            df_src_snk = df_src.loc[df_src['sink reference ID'] == snk_id]
            iter_vecs[(src_id, snk_id)] = list(df_src_snk['source iteration vector'])
    return iter_vecs

def gen_input_output_examples_for_ibound(bench, parms, df):
    src_ref_id = df['source reference ID'][0]
    num_of_nested_loops = len(df['iteration vector'][0].strip().split(' '))
    loop_name = ['loop ' + str(x) for x in range(num_of_nested_loops)]
    if num_of_nested_loops <= 1:
        df['loop 0'] = df['iteration vector']
    else:
        df[loop_name] = df['iteration vector'].str.split(' ', num_of_nested_loops - 1, expand=True)

    for i in range(num_of_nested_loops):
        df['loop ' + str(i)] = df['loop ' + str(i)].astype(int)

    for i in range(num_of_nested_loops):
        fmin = open(ioe_data_path + bench + '/ibound/' + bench + '_refsrc_' + str(
            src_ref_id) + '.imin' + str(i) + '.ibound', 'w')
        fmax = open(ioe_data_path + bench + '/ibound/' + bench + '_refsrc_' + str(
            src_ref_id) + '.imax' + str(i) + '.ibound', 'w')
        for parm in parms:
            df_bound = df.loc[df['bound values'] == get_parms_str_space(parm)]
            parm = get_parms_str_space(parm).split()
            entry = ''
            for idx in range(len(parm)):
                entry += 'b' + str(idx) + ' ' + parm[idx] + ' '
            fmin.write(entry + '_out ' + str(df_bound['loop ' + str(i)].min()) + '\n')
            fmax.write(entry + '_out ' + str(df_bound['loop ' + str(i)].max()) + '\n')
        fmin.close()
        fmax.close()

def gen_input_output_examples(bench, parms, spec, df, ref_ids, iter_vecs, cache_config):
    if (spec == 'src_only' and isinstance(ref_ids, int)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids)
            src_iv_ = iter_vec.replace(' ', '_')
            f = open(ioe_path + bench + '/' + spec + '/' + bench + '_refsrc_' + src_id + '_isrc_' + src_iv_ + '.ri.' + cache_config, 'w')
            for parm in parms:
                parm_str = get_parms_str_space(parm)
                # FIXME: all data in df should be read as string
                rows = df.loc[(df['bound values'] == parm_str) & (df['source iteration vector'] == iter_vec) & (df['source reference ID'] == int(src_id))]

                line = ''
                src_iv = iter_vec.split()
                for idx in range(len(src_iv)):
                    line += 'isrc' + str(idx) + ' ' + src_iv[idx] + ' '
                for idx in range(len(parm)):
                    line += 'b' + str(idx) + ' ' + str(parm[idx]) + ' '
                output = ''
                if (len(rows) == 1):
                    output = str(rows['reuse interval'].values[0])
                elif (len(rows) == 0):
                    output = str(0);
                else:
                    print 'Error: rows should be leq to one'
                    continue
                line += '_out ' + output + '\n'
                f.write(line)
            f.close()

    if ((spec == 'src_snk' or spec == 'src_snk_plus') and isinstance(ref_ids, tuple)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids[0])
            snk_id = str(ref_ids[1])
            src_iv_ = iter_vec.replace(' ', '_')
            f = open(ioe_path + bench + '/' + spec + '/' + bench + '_refsrc_' + src_id + '_refsnk_' + snk_id + '_isrc_' + src_iv_ + '.ri.' + cache_config,'w')
            for parm in parms:
                parm_str = get_parms_str_space(parm)
                # FIXME: all data in df should be read as string
                rows = df.loc[(df['bound values'] == parm_str) & (df['source iteration vector'] == iter_vec) &
                              (df['source reference ID'] == int(src_id)) & (df['sink reference ID'] == int(src_id))]
                line = ''
                src_iv = iter_vec.split()
                for idx in range(len(src_iv)):
                    line += 'isrc' + str(idx) + ' ' + src_iv[idx] + ' '
                for idx in range(len(parm)):
                    line += 'b' + str(idx) + ' ' + str(parm[idx]) + ' '
                output = ''
                if (len(rows) == 1):
                    output = str(rows['reuse interval'].values[0])
                elif (len(rows) == 0):
                    output = str(0);
                else:
                    print "Error: rows should be leq to one"
                line += '_out ' + output + '\n'
                f.write(line)
            f.close()

