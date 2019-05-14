package com.hzy.libpng;

import android.graphics.Bitmap;

public class NativePng {

    public static NativePng createFromBuffer(byte[] buffer) {
        return new NativePng(buffer);
    }

    private long mInstanceId;
    private int mWidth, mHeight;
    private final Bitmap mBitmap;

    private NativePng(byte[] buffer) {
        mInstanceId = LibPngApi.readFromBuffer(buffer);
        int[] size = new int[2];
        LibPngApi.getImageSize(mInstanceId, size);
        mWidth = size[0];
        mHeight = size[1];
        mBitmap = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
        int[] imageBytes = LibPngApi.getImagePixels(mInstanceId);
        mBitmap.setPixels(imageBytes, 0, mWidth, 0, 0, mWidth, mHeight);
    }

    public Bitmap getBitmap() {
        return mBitmap;
    }

    public void release() {
        LibPngApi.release(mInstanceId);
        mInstanceId = 0;
    }
}
