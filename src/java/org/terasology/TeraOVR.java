package org.terasology;

/*
 * Copyright 2012 Benjamin Glatzel <benjamin.glatzel@me.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class TeraOVR {

    public static native void initSDK();
    public static native void clear();

    public static native String getDisplayDeviceName();
    public static native String getProductName();
    public static native String getManufacturer();
    public static native int getVersion();
    public static native int getHResolution();
    public static native int getVResolution();
    public static native float getVScreenSize();
    public static native float getVScreenCenter();
    public static native float getEyeToScreenDistance();
    public static native float getLensSeparationDistance();
    public static native float getInterpupillaryDistance();
    public static native float getDistortitionK0();
    public static native float getDistortitionK1();
    public static native float getDistortitionK2();
    public static native float getDistortitionK3();

    public static native float getYaw();
    public static native float getPitch();
    public static native float getRoll();

    static {
        if (System.getProperty("os.arch").contains("64")) {
            System.loadLibrary("TeraOVR_x64");
        } else {
            System.loadLibrary("TeraOVR");
        }
    }

    public static void main(String[] args) {
        initSDK();

        System.out.println(getDisplayDeviceName());
        System.out.println(getProductName());
        System.out.println(getManufacturer());
        System.out.println(getVersion());
        System.out.println(getHResolution());
        System.out.println(getVResolution());
        System.out.println(getVScreenSize());
        System.out.println(getVScreenCenter());
        System.out.println(getEyeToScreenDistance());
        System.out.println(getLensSeparationDistance());
        System.out.println(getInterpupillaryDistance());
        System.out.println(getDistortitionK0());
        System.out.println(getDistortitionK1());
        System.out.println(getDistortitionK2());
        System.out.println(getDistortitionK3());

        while (true) {
            System.out.println("Yaw: " + getYaw() * (180.0f / Math.PI));
            System.out.println("Pitch: " + getPitch() * (180.0f / Math.PI));
            System.out.println("Roll: " + getRoll() * (180.0f / Math.PI));

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
            }
        }
    }
}
