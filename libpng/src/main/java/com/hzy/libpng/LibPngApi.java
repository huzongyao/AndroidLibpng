package com.hzy.libpng;

public class LibPngApi {

    static {
        System.loadLibrary("png");
    }

    public static native String getVersionString();

    public static native long readFromBuffer(byte[] buffer);

    public static native int getImageSize(long instanceId, int[] size);

    public static native int[] getImagePixels(long instanceId);

    public static native int release(long instanceId);
}
