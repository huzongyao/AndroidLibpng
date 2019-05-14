package com.hzy.libpng.demo.utils;

import com.blankj.utilcode.util.Utils;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class AssetsUtils {

    private static final int BUFFER_SIZE = 8192;

    public static byte[] readBytes(String name) {
        try {
            return is2Bytes(Utils.getApp().getAssets().open(name));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new byte[0];
    }

    private static byte[] is2Bytes(final InputStream is) {
        if (is == null) return null;
        ByteArrayOutputStream os = null;
        try {
            os = new ByteArrayOutputStream();
            byte[] b = new byte[BUFFER_SIZE];
            int len;
            while ((len = is.read(b, 0, BUFFER_SIZE)) != -1) {
                os.write(b, 0, len);
            }
            return os.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                if (os != null) {
                    os.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
