//
// Created by huzongyao on 2019/5/13.
//

#include <jni.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>

#ifdef NATIVE_LOG
#define LOG_TAG "NATIVE.LOG"

#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...) do{}while(0)
#define LOGI(...) do{}while(0)
#define LOGW(...) do{}while(0)
#define LOGE(...) do{}while(0)
#define LOGF(...) do{}while(0)
#endif

typedef struct {
    png_image *image_p;
    png_byte *out_buffer;
    size_t out_size;
} png_object;

#define JAVA_FUNC(f) Java_com_hzy_libpng_LibPngApi_##f

JNIEXPORT jstring JNICALL
JAVA_FUNC(getVersionString)(JNIEnv *env, jclass type) {
    return (*env)->NewStringUTF(env, PNG_LIBPNG_VER_STRING);
}

JNIEXPORT jlong JNICALL
JAVA_FUNC(readFromBuffer)(JNIEnv *env, jclass type, jbyteArray buffer_) {
    jbyte *buffer = (*env)->GetByteArrayElements(env, buffer_, NULL);
    jsize length = (*env)->GetArrayLength(env, buffer_);

    png_object *png_handler = malloc(sizeof(png_object));
    png_handler->image_p = malloc(sizeof(png_image));
    memset(png_handler->image_p, 0, sizeof(png_image));
    png_handler->image_p->version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_memory(png_handler->image_p, buffer, (size_t) length) != 0) {
        // PNG_FORMAT_BGRA just as Bitmap.Config.ARGB_8888 in android Bitmap.
        // byte[] BGRA buffer just the same as int[] ARGB, it's the little edition
        png_handler->image_p->format = PNG_FORMAT_BGRA;
        png_handler->out_size = PNG_IMAGE_SIZE(*png_handler->image_p);
        png_handler->out_buffer = malloc(png_handler->out_size);
        LOGE("Buffer Length: [%ld]", png_handler->out_size);
        if (png_image_finish_read(png_handler->image_p, NULL, png_handler->out_buffer, 0, NULL)
            != 0) {
            LOGE("PNG Parse OK!");
        }
    }
    (*env)->ReleaseByteArrayElements(env, buffer_, buffer, 0);
    return (jlong) png_handler;
}

JNIEXPORT jint JNICALL
JAVA_FUNC(getImageSize)(JNIEnv *env, jclass type, jlong instanceId, jintArray size_) {
    jint *size = (*env)->GetIntArrayElements(env, size_, NULL);
    if (instanceId != NULL) {
        png_object *png_handler = (png_object *) instanceId;
        size[0] = (jint) png_handler->image_p->width;
        size[1] = (jint) png_handler->image_p->height;
        LOGE("Image Size: [%dX%d]", size[0], size[1]);
    }
    (*env)->ReleaseIntArrayElements(env, size_, size, 0);
    return 0;
}

JNIEXPORT jintArray JNICALL
JAVA_FUNC(getImagePixels)(JNIEnv *env, jclass type, jlong instanceId) {
    if (instanceId != NULL) {
        png_object *png_handler = (png_object *) instanceId;
        jbyteArray ret = (*env)->NewIntArray(env, (jsize) (png_handler->out_size / 4));
        (*env)->SetIntArrayRegion(env, ret, 0, (jsize) (png_handler->out_size / 4),
                                  (jint *) png_handler->out_buffer);
        return ret;
    }
    return NULL;
}

JNIEXPORT jint JNICALL
JAVA_FUNC(release)(JNIEnv *env, jclass type, jlong instanceId) {
    if (instanceId != NULL) {
        png_object *png_handler = (png_object *) instanceId;
        free(png_handler->image_p);
        free(png_handler->out_buffer);
        free(png_handler);
    }
    return 0;
}