
package com.huawei.adplugin.adproxy;

import android.app.Activity;
import android.graphics.Color;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;
import android.util.Log;

import com.huawei.hms.ads.AdListener;
import com.huawei.hms.ads.AdParam;
import com.huawei.hms.ads.BannerAdSize;
import com.huawei.hms.ads.banner.BannerView;
import com.huawei.adplugin.Const;
import com.huawei.adplugin.adlistener.IAdStatusListener;

public class BannerAdProxy extends AdListener {
    private static final int DEFAULT_WIDTH = 320;

    private Activity mActivity;

    private BannerView mBannerView;

    private IAdStatusListener mAdListener;

    private Handler mMainThreadHandler = new Handler(Looper.getMainLooper());

    private String mAdId;

    private String mAdSizeType = Const.BannerAdSize.USER_DEFINED;

    private int mPositionCode = Const.BannerAdPositionCode.POSITION_TOP;

    private int mHorizontalOffset = 0;

    private int mVerticalOffset = 0;

    private boolean mIsHide = false;

    private int mCustomWidth = DEFAULT_WIDTH;

    private long bannerRefresh = 60;

    private int bannerViewWidth,bannerViewHeight;

    private static final String TAG = "BannerAdProxy";

    public BannerAdProxy(Activity activity, IAdStatusListener listener) {
        mActivity = activity;
        mAdListener = listener;

        int width = activity.getWindow().getDecorView().getWidth();
        int height = activity.getWindow().getDecorView().getHeight();

        if(width>height)
        {
            bannerViewWidth = (int) (width*0.55);
            bannerViewHeight= (int) (height*0.20);
        }
        else
        {
            bannerViewWidth = (int) (width*0.8);
            bannerViewHeight= FrameLayout.LayoutParams.WRAP_CONTENT;//(int) (height*0.10);
        }
    }

    public void setAdId(String adId) {
        mAdId = adId;
    }

    public void setAdSizeType(String adSizeType) {
        mAdSizeType = adSizeType;
    }

    /*
    public void setBannerRefresh(long interval) {
        bannerRefresh = interval;
        if (bannerView != null)
            bannerView.setBannerRefresh(interval);
    }
    */

    public void loadAd(final AdParam adRequest) {
        mMainThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                if (mBannerView == null) {
                    mBannerView = new BannerView(mActivity);
                    mBannerView.setBackgroundColor(Color.TRANSPARENT);
                    mBannerView.setVisibility(View.GONE);
                    mBannerView.setAdListener(BannerAdProxy.this);
                    mBannerView.setBannerRefresh(bannerRefresh);
                    mActivity.addContentView(mBannerView, getBannerViewLayoutParams(bannerViewWidth,bannerViewHeight));
                }
                mBannerView.setAdId(mAdId);
                mBannerView.setBannerAdSize(getTargetBannerAdSize(mAdSizeType));
                Log.i(TAG, "Load ad with id " + mAdId + "; size: " + mBannerView.getBannerAdSize());    

                if (BannerAdSize.BANNER_SIZE_INVALID.equals(mBannerView.getBannerAdSize())) {
                    return;
                }

                if (TextUtils.isEmpty(mBannerView.getAdId())) {
                    return;
                }
                mBannerView.loadAd(adRequest);
            }
        });
    }

    public void setCustomSize(int size) {
        mCustomWidth = size;
    }

    public void show() {
        mMainThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                mIsHide = false;
                if (mBannerView != null) {
                    mBannerView.resume();
                    mBannerView.setVisibility(View.VISIBLE);
                }
            }
        });
    }

    public void hide() {
        mMainThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                mIsHide = true;
                if (mBannerView != null) {
                    mBannerView.pause();
                    mBannerView.setVisibility(View.GONE);
                }
            }
        });
    }

    public void destroy() {
        mMainThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                if (mBannerView != null) {
                    mBannerView.destroy();
                    mBannerView.setVisibility(View.GONE);
                    ViewParent parentView = mBannerView.getParent();
                    if (parentView instanceof ViewGroup) {
                        ((ViewGroup) parentView).removeView(mBannerView);
                    }
                }
                mBannerView = null;
            }
        });
    }

    public void setBannerAdPosition(final int positionX, final int positionY) {
        mPositionCode = Const.BannerAdPositionCode.POSITION_CUSTOM;
        mHorizontalOffset = positionX;
        mVerticalOffset = positionY;
        updatePosition();
    }

    public void setBannerAdPosition(final int positionCode) {
        mPositionCode = positionCode;
        mHorizontalOffset = 0;
        mVerticalOffset = 0;
        updatePosition();
    }

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
                if (!mIsHide && mBannerView != null) {
                    show();
                }
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

    private float convertDpToPx(float dp) {
        DisplayMetrics metrics = mActivity.getResources().getDisplayMetrics();
        return dp * metrics.density;
    }

    private BannerAdSize getTargetBannerAdSize(String adSize) {
        BannerAdSize bannerAdSize = BannerAdSize.BANNER_SIZE_INVALID;
        switch (adSize) {
            case Const.BannerAdSize.USER_DEFINED:
                bannerAdSize = getUserDefinedBannerSize();
                break;
            case Const.BannerAdSize.BANNER_SIZE_320_50:
                bannerAdSize = BannerAdSize.BANNER_SIZE_320_50;
                break;
            case Const.BannerAdSize.BANNER_SIZE_320_100:
                bannerAdSize = BannerAdSize.BANNER_SIZE_320_100;
                break;
            case Const.BannerAdSize.BANNER_SIZE_468_60:
                bannerAdSize = BannerAdSize.BANNER_SIZE_468_60;
                break;
            case Const.BannerAdSize.BANNER_SIZE_DYNAMIC:
                bannerAdSize = BannerAdSize.BANNER_SIZE_DYNAMIC;
                break;
            case Const.BannerAdSize.BANNER_SIZE_728_90:
                bannerAdSize = BannerAdSize.BANNER_SIZE_728_90;
                break;
            case Const.BannerAdSize.BANNER_SIZE_300_250:
                bannerAdSize = BannerAdSize.BANNER_SIZE_300_250;
                break;
            case Const.BannerAdSize.BANNER_SIZE_SMART:
                bannerAdSize = BannerAdSize.BANNER_SIZE_SMART;
                break;
            case Const.BannerAdSize.BANNER_SIZE_160_600:
                bannerAdSize = BannerAdSize.BANNER_SIZE_160_600;
                break;
            case Const.BannerAdSize.BANNER_SIZE_360_57:
                bannerAdSize = BannerAdSize.BANNER_SIZE_360_57;
                break;
            case Const.BannerAdSize.BANNER_SIZE_360_144:
                bannerAdSize = BannerAdSize.BANNER_SIZE_360_144;
                break;
            default:
                break;
        }
        return bannerAdSize;
    }

    private BannerAdSize getUserDefinedBannerSize() {
        return BannerAdSize.getCurrentDirectionBannerSize(mActivity, mCustomWidth);
    }

    private FrameLayout.LayoutParams getBannerViewLayoutParams(int width,int height) {

    /*
        final FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                FrameLayout.LayoutParams.WRAP_CONTENT);
                */

        final FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(width, height);

        adParams.gravity = Const.BannerAdPositionCode.getLayoutGravityForPositionCode(mPositionCode);
        int safeInsetLeft = 0;
        int safeInsetTop = 0;
        if (mPositionCode == Const.BannerAdPositionCode.POSITION_CUSTOM) {
            int leftOffset = (int) convertDpToPx(mHorizontalOffset);
            if (leftOffset < safeInsetLeft) {
                leftOffset = safeInsetLeft;
            }
            int topOffset = (int) convertDpToPx(mVerticalOffset);
            if (topOffset < safeInsetTop) {
                topOffset = safeInsetTop;
            }

            //adParams.leftMargin = leftOffset;
            adParams.leftMargin = 0;
            //adParams.topMargin = topOffset;
            adParams.topMargin = (int)(mActivity.getWindow().getDecorView().getHeight()*0.06);//topOffset;

        } else {
            adParams.leftMargin = safeInsetLeft;
            if (mPositionCode == Const.BannerAdPositionCode.POSITION_TOP
                    || mPositionCode == Const.BannerAdPositionCode.POSITION_TOP_LEFT
                    || mPositionCode == Const.BannerAdPositionCode.POSITION_TOP_RIGHT) {
                adParams.topMargin = safeInsetTop;
            }
        }
        return adParams;
    }
    
    /*
    private FrameLayout.LayoutParams getBannerViewLayoutParams(int width,int height) {
      Log.d(TAG,"getBannerViewLayoutParams Width:"+width+" Height:"+height);
      final FrameLayout.LayoutParams adParams =
              new FrameLayout.LayoutParams(width, height);
      adParams.gravity = UnityBannerAdPositionCode.getLayoutGravityForPositionCode(positionCode);
      int safeInsetLeft = 0;
      int safeInsetTop = 0;//(int)(height*0.35);
      if (positionCode == UnityBannerAdPositionCode.POSITION_CUSTOM) {
          int leftOffset = (int) convertDpToPx(horizontalOffset);
          if (leftOffset < safeInsetLeft) {
              leftOffset = safeInsetLeft;
          }
          int topOffset = (int) convertDpToPx(verticalOffset);
          if (topOffset < safeInsetTop) {
              topOffset = safeInsetTop;
          }
          adParams.leftMargin = 0;//leftOffset;
          adParams.topMargin = (int)(activity.getWindow().getDecorView().getHeight()*0.06);//topOffset;
      } else {
          adParams.leftMargin = safeInsetLeft;
          if (positionCode == UnityBannerAdPositionCode.POSITION_TOP
                  || positionCode == UnityBannerAdPositionCode.POSITION_TOP_LEFT
                  || positionCode == UnityBannerAdPositionCode.POSITION_TOP_RIGHT) {
              adParams.topMargin = safeInsetTop;
          }
      }
      return adParams;
    }
    */

    private void updatePosition() {
        mMainThreadHandler.post(new Runnable() {
            @Override
            public void run() {
                if (mBannerView == null) {
                    return;
                }
                FrameLayout.LayoutParams layoutParams = getBannerViewLayoutParams(bannerViewWidth,bannerViewHeight);
                mBannerView.setLayoutParams(layoutParams);
            }
        });
    }
}
