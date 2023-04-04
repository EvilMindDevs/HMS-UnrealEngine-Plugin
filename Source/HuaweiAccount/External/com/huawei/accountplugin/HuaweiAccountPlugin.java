package com.huawei.accountplugin;

import android.app.NativeActivity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import com.huawei.hmf.tasks.OnFailureListener;
import com.huawei.hmf.tasks.OnSuccessListener;
import com.huawei.hmf.tasks.Task;
import com.huawei.hms.common.ApiException;
import com.huawei.hms.support.account.AccountAuthManager;
import com.huawei.hms.support.account.request.AccountAuthParams;
import com.huawei.hms.support.account.request.AccountAuthParamsHelper;
import com.huawei.hms.support.account.result.AuthAccount;
import com.huawei.hms.support.account.service.AccountAuthService;

public class HuaweiAccountPlugin {
    private static boolean isInit = false;
    private static NativeActivity mActivity = null;
    private static HuaweiAccountListener mListener = null;
    private static final String TAG = "HuaweiAccountPlugin";
    private static final String MODE = "HUAWEI_LOGIN_MODE";
    private static final String PREFS_NAME = "com.huawei.accountplugin";
    private static SharedPreferences mSharedPreferences;
    
    public static void initialize(NativeActivity activity, HuaweiAccountListener listener) {
        if (!isInit) {
            mActivity = activity;
            mListener = listener;
            mSharedPreferences = mActivity.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
            isInit = true;
        }
    }

    public static void loginWithoutVerification() {
        login(Constants.LOGIN_ACTION);
    }

    public static void loginWithIdToken() {
        login(Constants.LOGIN_BY_ID_TOKEN_ACTION);
    }

    public static void loginWithAuthorizationCode() {
        login(Constants.LOGIN_BY_AUTH_CODE_ACTION);
    }

    public static void registerOnActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case Constants.REQUEST_LOGIN:
            case Constants.REQUEST_LOGIN_BY_AUTH_CODE:
            case Constants.REQUEST_LOGIN_BY_ID_TOKEN:
                parseAuthResult(requestCode, data);    
                break;
            default:
                break;    
        }
    } 

    public static void logOut() {
        int action = mSharedPreferences.getInt(MODE, Constants.LOGIN_ACTION);
        AccountAuthService authService = createAuthService(action);
        Task<Void> signOutTask = authService.signOut();
        signOutTask.addOnSuccessListener(new OnSuccessListener<Void>() {
            @Override
            public void onSuccess(Void aVoid) {
                Log.i(TAG, "signOut Success");
                if (mListener != null) {
                    mListener.onLoggedOut();
                }
            }
        }).addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(Exception e) {
                Log.i(TAG, "signOut fail");
                if (mListener != null) {
                    mListener.onException(Constants.LOGOUT_ACTION, e.getMessage());
                }
            }
        });
    }

    public static void cancelAuthorization() {
        int action = mSharedPreferences.getInt(MODE, Constants.LOGIN_ACTION);
        AccountAuthService authService = createAuthService(action);
        Task<Void> task = authService.cancelAuthorization();
        task.addOnSuccessListener(new OnSuccessListener<Void>() {
            @Override
            public void onSuccess(Void aVoid) {
                Log.i(TAG, "cancelAuthorization success");
                if (mListener != null) {
                    mListener.onCancelledAuth();
                }
            }
        });
        task.addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(Exception e) {
                Log.i(TAG, "cancelAuthorization failure:" + e.getMessage());
                if (mListener != null) {
                    mListener.onException(Constants.CANCEL_AUTH_ACTION, e.getMessage());
                }
            }
        });
    }

    private static void login(final int action) {
        final AccountAuthService authService = createAuthService(action);
        Task<AuthAccount> task = authService.silentSignIn();
        task.addOnSuccessListener(new OnSuccessListener<AuthAccount>() {
            @Override
            public void onSuccess(AuthAccount authAccount) {
                // The silent sign-in is successful. Process the returned account object
                // AuthAccount to obtain the HUAWEI ID information.
                onLoginResult(action, authAccount);
            }
        });
        task.addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(Exception e) {
                // The silent sign-in fails. Your app will call getSignInIntent() to show the
                // authorization or sign-in screen.
                Log.e(TAG, "On log in fail: " +e.getMessage());
                int requestCode;
                switch (action) {
                    case Constants.LOGIN_BY_ID_TOKEN_ACTION:
                        requestCode = Constants.REQUEST_LOGIN_BY_ID_TOKEN;
                        break;
                    case Constants.LOGIN_BY_AUTH_CODE_ACTION:
                        requestCode = Constants.REQUEST_LOGIN_BY_AUTH_CODE;
                        break;
                    default:
                        requestCode = Constants.REQUEST_LOGIN;
                        break;    
                }
                if (e instanceof ApiException) {
                    ApiException apiException = (ApiException) e;
                    mActivity.startActivityForResult(authService.getSignInIntent(), requestCode);
                } else {
                    if (mListener != null) {
                        mListener.onException(action, e.getMessage());
                    }
                }
            }
        });
    }

    private static AccountAuthService createAuthService(int action) {
        AccountAuthParamsHelper authParamHelper = new AccountAuthParamsHelper(AccountAuthParams.DEFAULT_AUTH_REQUEST_PARAM).setEmail().setId();
        switch (action) {
            case Constants.LOGIN_BY_ID_TOKEN_ACTION:
                authParamHelper = authParamHelper.setIdToken();
                break;
            case Constants.LOGIN_BY_AUTH_CODE_ACTION:
                authParamHelper = authParamHelper.setAuthorizationCode();
                break;
            default:
                break;    
        }
        AccountAuthParams authParam = authParamHelper.createParams();
        return AccountAuthManager.getService(mActivity, authParam);
    }

    private static void parseAuthResult(int requestCode, Intent data) {
        int action;
        switch (requestCode) {
            case Constants.REQUEST_LOGIN_BY_AUTH_CODE:
                action = Constants.LOGIN_BY_AUTH_CODE_ACTION;
                break;
            case Constants.REQUEST_LOGIN_BY_ID_TOKEN:
                action = Constants.LOGIN_BY_ID_TOKEN_ACTION;
                break;       
            default:
                action = Constants.LOGIN_ACTION;
                break; 
        }
        Task<AuthAccount> authAccountTask = AccountAuthManager.parseAuthResultFromIntent(data);
        if (authAccountTask.isSuccessful()) {
            // The sign-in is successful, and the authAccount object that contains the HUAWEI ID information is obtained.
            AuthAccount authAccount = authAccountTask.getResult();
            Log.i(TAG, "onActivityResult of sigInInIntent, request code: " + requestCode);
            onLoginResult(action, authAccount);
        } else {
            // The sign-in failed. Find the failure cause from the status code. For more information, please refer to Error Codes.
            String message = "sign in failed : " +((ApiException)authAccountTask.getException()).getStatusCode();
            Log.e(TAG, message);
            if (mListener != null) {
                mListener.onException(action, message);
            }
        }
    }

    private static void onLoginResult(int action, AuthAccount authAccount) {
        Log.d(TAG, "On logged in result");
        mSharedPreferences.edit().putInt(MODE, action).apply();
        if (mListener != null) {
            switch (action) {
                case Constants.LOGIN_BY_ID_TOKEN_ACTION:
                    mListener.onGetIdToken(authAccount);
                    break;
                case Constants.LOGIN_BY_AUTH_CODE_ACTION:
                    mListener.onGetAuthCode(authAccount);
                    break;
                default:
                    mListener.onLoggedIn(authAccount);
                    break;    
            }
        }
    }
}
