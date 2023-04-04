
package com.huawei.adplugin.adproxy;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;

import com.huawei.hms.ads.AdListener;
import com.huawei.hms.ads.AdParam;
import com.huawei.hms.ads.InterstitialAd;
import com.huawei.adplugin.adlistener.IAdStatusListener;

public class InterstitialAdProxy {
    private Context mContext;

    private InterstitialAd mInterstitialAd;

    private IAdStatusListener mAdListener;

    private Handler mMainThreadHandler = new Handler(Looper.getMainLooper());

    public InterstitialAdProxy(Context context) {
        mContext = context;
        mInterstitialAd = new InterstitialAd(mContext);
    }

    public void setAdListener(IAdStatusListener adStatusListener) {
        mAdListener = adStatusListener;
        mInterstitialAd.setAdListener(new AdListener() {
            @Override
            public void onAdClosed() {
                super.onAdClosed();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdClosed();
                        }
                    }
                });
            }

            @Override
            public void onAdFailed(final int errorCode) {
                super.onAdFailed(errorCode);
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdFailed(errorCode);
                        }
                    }
                });
            }

            @Override
            public void onAdLeave() {
                super.onAdLeave();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdLeftApp();
                        }
                    }
                });
            }

            @Override
            public void onAdOpened() {
                super.onAdOpened();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdOpened();
                        }
                    }
                });
            }

            @Override
            public void onAdLoaded() {
                super.onAdLoaded();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdLoaded();
                        }
                    }
                });
            }

            @Override
            public void onAdClicked() {
                super.onAdClicked();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdClicked();
                        }
                    }
                });
            }

            @Override
            public void onAdImpression() {
                super.onAdImpression();
                mMainThreadHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mAdListener != null) {
                            mAdListener.onAdImpression();
                        }
                    }
                });
            }
        });
    }

    public void setAdId(String adId) {
        mInterstitialAd.setAdId(adId);
    }

    public boolean isLoaded() {
        return mInterstitialAd.isLoaded();
    }

    public boolean isLoading() {
        return mInterstitialAd.isLoading();
    }

    public void loadAd(AdParam adRequest) {
        mInterstitialAd.loadAd(adRequest);
    }

    public void show() {
        mInterstitialAd.show();
    }
}
