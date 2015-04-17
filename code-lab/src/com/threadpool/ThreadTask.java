package com.threadpool;

import com.threadpool.Impl.WorkIssuesImpl;
import com.threadpool.Model.DataModel;
import com.threadpool.Model.ResultModel;

import javax.annotation.Resource;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Callable;

/**
 * Created by wenyun on 2015-03-19 18:35.
 */

public class ThreadTask implements Callable<ResultModel> {

    Integer threadId = null;

    String name = null;

    String actionType = null;

    @Resource
    private WorkIssuesImpl workIssues;

    public ThreadTask(String name, Integer id, String actionType) {
        if (id != null) {
            this.threadId = id;
            this.name = name;
            this.actionType = actionType;
        }
        workIssues = new WorkIssuesImpl();
    }
    public String getThreadName() {
        return this.name;
    }

    public Integer getThreadId () {
        return this.threadId;
    }

    @Override
    public ResultModel call() {
        DataModel dataModel = new DataModel();
        dataModel.setId(getThreadId());
        dataModel.setName(getThreadName());
        Map<String,Object> resMore = new HashMap<String, Object>();
        resMore.put("id",getThreadId());
        resMore.put("name",getThreadName());
        resMore.put("actionType",actionType);
        dataModel.setMore(resMore);
        return workIssues.doWorkIssues(dataModel);
    }
}
