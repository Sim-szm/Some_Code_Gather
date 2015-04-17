package com.threadpool.Impl;

import com.threadpool.Model.DataModel;
import com.threadpool.Model.ResultModel;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by wenyun on 2015-04-16 17:25.
 */
public class FoodExploreService extends AbstractService {

    public String getContent(DataModel dataModel) {
        StringBuilder contentBuf = new StringBuilder();
        String strURL = "http://search.yunos.com/api/search?q=周边美食&loc=118.752266,31.973765&format=json";
        try {
            URL url = new URL(strURL);
            HttpURLConnection httpConn = (HttpURLConnection) url.openConnection();
            InputStreamReader input = new InputStreamReader(httpConn.getInputStream(), "utf-8");
            BufferedReader bufReader = new BufferedReader(input);
            String line = "";
            while ((line = bufReader.readLine()) != null) {
                contentBuf.append(line);
            }
        }catch (IOException e) {
            System.out.println(e.getStackTrace());
        }
        return contentBuf.toString();
    }

    @Override
    public ResultModel resultBack(DataModel dataModel) {
        ResultModel resultModel = new ResultModel();
        Map<String, Object> info = new HashMap<String, Object>();
        info.put("saltResult",getContent(dataModel));
        resultModel.setId(dataModel.getId());
        resultModel.setName(dataModel.getName());
        resultModel.setMore(info);
        return resultModel;
    }

}
