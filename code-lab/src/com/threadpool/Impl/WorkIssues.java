package com.threadpool.Impl;

import com.threadpool.Model.DataModel;
import com.threadpool.Model.ResultModel;

/**
 * Created by wenyun on 2015-04-16 11:52.
 */
public interface WorkIssues {

    /**
     * make some salt for data !
     */
    public String addSalt(DataModel dataModel);

    /**
     * real work issues function !
     */
    public ResultModel doWorkIssues(DataModel dataModel) ;
}
