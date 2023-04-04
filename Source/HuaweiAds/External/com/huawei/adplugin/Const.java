package com.huawei.adplugin;

import android.view.Gravity;

public class Const {
    public static final class BannerAdSize {
        public static final String USER_DEFINED = "USER_DEFINED";

        public static final String BANNER_SIZE_320_50 = "BANNER_SIZE_320_50";

        public static final String BANNER_SIZE_320_100 = "BANNER_SIZE_320_100";

        public static final String BANNER_SIZE_468_60 = "BANNER_SIZE_468_60";

        public static final String BANNER_SIZE_DYNAMIC = "BANNER_SIZE_DYNAMIC";

        public static final String BANNER_SIZE_728_90 = "BANNER_SIZE_728_90";

        public static final String BANNER_SIZE_300_250 = "BANNER_SIZE_300_250";

        public static final String BANNER_SIZE_SMART = "BANNER_SIZE_SMART";

        public static final String BANNER_SIZE_160_600 = "BANNER_SIZE_160_600";

        public static final String BANNER_SIZE_360_57 = "BANNER_SIZE_360_57";

        public static final String BANNER_SIZE_360_144 = "BANNER_SIZE_360_144";
    }

    public static final class BannerAdPositionCode {
        /**
         * Position constant for a position with a custom offset.
         */
        public static final int POSITION_CUSTOM = -1;

        /**
         * Position constant for top of the screen.
         */
        public static final int POSITION_TOP = 0;

        /**
         * Position constant for bottom of the screen.
         */
        public static final int POSITION_BOTTOM = 1;

        /**
         * Position constant for top-left of the screen.
         */
        public static final int POSITION_TOP_LEFT = 2;

        /**
         * Position constant for top-right of the screen.
         */
        public static final int POSITION_TOP_RIGHT = 3;

        /**
         * Position constant for bottom-left of the screen.
         */
        public static final int POSITION_BOTTOM_LEFT = 4;

        /**
         * Position constant bottom-right of the screen.
         */
        public static final int POSITION_BOTTOM_RIGHT = 5;

        /**
         * Position constant center of the screen.
         */
        public static final int POSITION_CENTER = 6;

        public static int getLayoutGravityForPositionCode(int positionCode) {
            int gravity;
            switch (positionCode) {
                case POSITION_TOP:
                    gravity = Gravity.TOP | Gravity.CENTER_HORIZONTAL;
                    break;
                case POSITION_BOTTOM:
                    gravity = Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL;
                    break;
                case POSITION_TOP_LEFT:
                    gravity = Gravity.TOP | Gravity.LEFT;
                    break;
                case POSITION_TOP_RIGHT:
                    gravity = Gravity.TOP | Gravity.RIGHT;
                    break;
                case POSITION_BOTTOM_LEFT:
                    gravity = Gravity.BOTTOM | Gravity.LEFT;
                    break;
                case POSITION_BOTTOM_RIGHT:
                    gravity = Gravity.BOTTOM | Gravity.RIGHT;
                    break;
                case POSITION_CENTER:
                    gravity = Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL;
                    break;
                case POSITION_CUSTOM:
                    gravity = Gravity.TOP | Gravity.LEFT;
                    break;
                default:
                    throw new IllegalArgumentException("Attempted to position ad with invalid ad " + "position.");
            }
            return gravity;
        }
    }
}
