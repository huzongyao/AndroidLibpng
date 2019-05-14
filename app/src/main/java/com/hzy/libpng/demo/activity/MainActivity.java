package com.hzy.libpng.demo.activity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;
import android.widget.TextView;

import com.hzy.libpng.LibPngApi;
import com.hzy.libpng.NativePng;
import com.hzy.libpng.demo.R;
import com.hzy.libpng.demo.utils.AssetsUtils;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MainActivity extends AppCompatActivity {

    @BindView(R.id.version_string)
    TextView mVersionString;
    @BindView(R.id.show_image)
    ImageView mShowImage;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        getVersionInfo();
        readDemoPng();
    }

    @SuppressLint("SetTextI18n")
    private void getVersionInfo() {
        mVersionString.setText("libpng version: " + LibPngApi.getVersionString());
    }

    private void readDemoPng() {
        byte[] fileBytes = AssetsUtils.readBytes("demo.png");
        NativePng nativePng = NativePng.createFromBuffer(fileBytes);
        mShowImage.setImageBitmap(nativePng.getBitmap());
        nativePng.release();
    }
}
