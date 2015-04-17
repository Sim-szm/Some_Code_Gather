package com.threadpool.Impl;

import com.threadpool.Model.DataModel;
import com.threadpool.Model.ResultModel;
import com.threadpool.Model.ServiceType;

import java.util.Map;

/**
 * Created by wenyun on 2015-04-16 12:45.
 */
public class WorkIssuesImpl implements WorkIssues{

    private FetchService fetchService;

    public WorkIssuesImpl(){
        fetchService = new FetchService();
    }
    @Override
    public String addSalt(DataModel dataModel){
        //TODO should be changed as real workIssues salts
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("hiya, stranger ");
        stringBuilder.append(dataModel.getId());
        stringBuilder.append(" | ");
        return stringBuilder.toString() + " Time: " + System.currentTimeMillis();
    }

    @Override
    public ResultModel doWorkIssues(DataModel dataModel) {
        String type = (String) dataModel.getMore().get("actionType");
        ResultContent resultContent = fetchService.getServiceContent(ServiceType.valueOf(type));
        ResultModel resultModel = resultContent.resultBack(dataModel);
        Map<String, Object> moreInfo = resultModel.getMore();
        moreInfo.put("code",this.addSalt(dataModel));
        if (resultModel == null) {
            return null;
        }
        return resultModel;
    }
}
