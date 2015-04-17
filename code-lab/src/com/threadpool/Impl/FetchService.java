package com.threadpool.Impl;

import com.threadpool.Model.ServiceType;

/**
 * Created by wenyun on 2015-04-16 20:05.
 */
public class FetchService implements ServiceManager {

    @Override
    public ResultContent getServiceContent(ServiceType serviceType) {
        switch (serviceType) {
            case food:
                FoodExploreService foodExplore = new FoodExploreService();
                return foodExplore;
            case weather:
                return null;
            case car:
                return null;
        }
        return null;
    }

}
