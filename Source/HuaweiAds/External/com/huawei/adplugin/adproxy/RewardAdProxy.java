
package com.huawei.adplugin.adproxy;

import android.app.Activity;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.huawei.hms.ads.AdParam;
import com.huawei.hms.ads.reward.Reward;
import com.huawei.hms.ads.reward.RewardAd;
import com.huawei.hms.ads.reward.RewardAdLoadListener;
import com.huawei.hms.ads.reward.RewardAdStatusListener;
import com.huawei.hms.ads.reward.RewardVerifyConfig;
import com.huawei.adplugin.adlistener.IRewardAdLoadListener;
import com.huawei.adplugin.adlistener.IRewardAdStatusListener;

public class RewardAdProxy {
    private Activity mActivity;

    private RewardAd mRewardAd;

    private String mAdId;

    private IRewardAdStatusListener mAdStatusListener;

    private IRewardAdLoadListener mAdLoadListener;

    private Handler mMainThreadHandler = new Handler(Looper.getMainLooper());

    private static final String TAG = "RewardAdProxy";

    public RewardAdProxy(Activity activity, String adId) {
        mActivity = activity;
        mAdId = adId;
        mRewardAd = new RewardAd(mActivity, adId);
    }

    public void loadAd(AdParam adRequest, IRewardAdLoadListener rewardAdLoadListener) {
        mAdLoadListener = rewardAdLoadListener;
        if (adRequest != null) {
            mRewardAd.loadAd(adRequest, new RewardAdLoadListener() {
                @Override
                public void onRewardAdFailedToLoad(final int errorCode) {
                    Log.i(TAG, "Failed to load reward ad with error code " + errorCode);
                    super.onRewardAdFailedToLoad(errorCode);
                    mMainThreadHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            if (mAdLoadListener != null) {
                                mAdLoadListener.onRewardAdFailedToLoad(errorCode);
                            }
                        }
                    });
                }

                @Override
                public void onRewardedLoaded() {
                    Log.i(TAG, "Loaded reward ad");
                    super.onRewardedLoaded();
                    mMainThreadHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            if (mAdLoadListener != null) {
                                mAdLoadListener.onRewardedLoaded();
                            }
                        }
                    });
                }
            });
        }
    }

    public void loadandshow(AdParam adRequest) {
        if (adRequest != null) {
            mRewardAd.loadAd(adRequest, new RewardAdLoadListener() {
                @Override
                public void onRewardAdFailedToLoad(final int errorCode) {
                    Log.i(TAG, "Failed to load reward ad with error code " + errorCode);
                    super.onRewardAdFailedToLoad(errorCode);
                    mMainThreadHandler.post(new Runnable() {
                        @Override
                        public void run() {

                        }
                    });
                }

                @Override
                public void onRewardedLoaded() {
                    Log.i(TAG, "Loaded reward ad");
                    super.onRewardedLoaded();
                    mMainThreadHandler.post(new Runnable() {
                        @Override
                        public void run() {

                            if (mAdLoadListener != null) {
                                mAdLoadListener.onRewardedLoaded();
                            }
                        }
                    });
                }
            });
        }
    }

    public void show() {
        mRewardAd.show();
    }

    public void show(Activity activity, IRewardAdStatusListener adStatusListener) {
        mAdStatusListener = adStatusListener;
        mRewardAd.show(activity, new RewardAdStatusListener() {
            @Override
            public void onRewardAdClosed() {
                Log.i(TAG, "Closed reward ad");
                super.onRewardAdClosed();

                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdStatusListener != null) {
                            mAdStatusListener.onRewardAdClosed();
                        }
                    }
                });
            }

            @Override
            public void onRewardAdFailedToShow(final int errorCode) {
                Log.i(TAG, "Failed to show reward ad with error code " + errorCode);
                super.onRewardAdFailedToShow(errorCode);
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdStatusListener != null) {
                            mAdStatusListener.onRewardAdFailedToShow(errorCode);
                        }
                    }
                });
            }

            @Override
            public void onRewardAdOpened() {
                Log.i(TAG, "Opened reward ad");
                super.onRewardAdOpened();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdStatusListener != null) {
                            mAdStatusListener.onRewardAdOpened();
                        }
                    }
                });
            }

            @Override
            public void onRewarded(final Reward reward) {
                Log.i(TAG, "Rewarded with " + reward.getName() + "; " + reward.getAmount());
                super.onRewarded(reward);
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdStatusListener != null) {
                            int rewardAmount = reward.getAmount();
                            String rewardName = reward.getName() != null ? reward.getName() : "";
                            mAdStatusListener.onRewarded(rewardName, rewardAmount);
                        }
                    }
                });
            }
        });
    }

    public void setRewardVerifyConfig(RewardVerifyConfig config) {
        mRewardAd.setRewardVerifyConfig(config);
    }

    public boolean isLoaded() {
        return mRewardAd.isLoaded();
    }

    public void setData(String customData) {
        mRewardAd.setData(customData);
    }

    public void setUserId(String userId) {
        mRewardAd.setUserId(userId);
    }

    public String getRewardName() {
        Reward reward = mRewardAd.getReward();
        if (reward != null) {
            return mRewardAd.getReward().getName();
        } else {
            return "";
        }
    }

    public int getRewardAmount() {
        Reward reward = mRewardAd.getReward();
        if (reward != null) {
            return mRewardAd.getReward().getAmount();
        } else {
            return 0;
        }
    }
}
