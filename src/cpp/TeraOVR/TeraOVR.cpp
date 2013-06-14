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

#include "TeraOVR.h"

#include "OVR.h"
#include "jni.h"

#include <iostream>
#include <conio.h>

using namespace std;
using namespace OVR;

Ptr<DeviceManager> g_Manager;
Ptr<HMDDevice> g_HMD;
Ptr<SensorDevice>	g_Sensor;
SensorFusion g_FusionResult;
HMDInfo g_Info;
bool g_InfoLoaded;

JNIEXPORT void JNICALL Java_org_terasology_TeraOVR_initSDK
  (JNIEnv * p_Env, jclass p_Class)
{
  System::Init();

  g_Manager = *DeviceManager::Create();
  g_HMD = *g_Manager->EnumerateDevices<HMDDevice>().CreateDevice();

  if (g_HMD)
  {
    g_InfoLoaded = g_HMD->GetDeviceInfo(&g_Info);

    g_Sensor = *g_HMD->GetSensor();
  }
  else
  {
    g_Sensor = *g_Manager->EnumerateDevices<SensorDevice>().CreateDevice();
  }

  if (g_Sensor)
  {
    g_FusionResult.AttachToSensor(g_Sensor);
  }
}

JNIEXPORT void JNICALL Java_org_terasology_TeraOVR_clear
  (JNIEnv * p_Env, jclass p_Class)
{
  g_Sensor.Clear();
  g_HMD.Clear();
  g_Manager.Clear();

  System::Destroy();
}

JNIEXPORT jstring JNICALL Java_org_terasology_TeraOVR_getDisplayDeviceName
  (JNIEnv * p_Env, jclass p_Class)
{
  return p_Env->NewStringUTF(g_Info.DisplayDeviceName);
}

JNIEXPORT jstring JNICALL Java_org_terasology_TeraOVR_getProductName
  (JNIEnv * p_Env, jclass p_Class)
{
  return p_Env->NewStringUTF(g_Info.ProductName);
}

JNIEXPORT jstring JNICALL Java_org_terasology_TeraOVR_getManufacturer
  (JNIEnv * p_Env, jclass p_Class)
{
  return p_Env->NewStringUTF(g_Info.Manufacturer);
}

JNIEXPORT jint JNICALL Java_org_terasology_TeraOVR_getVersion
  (JNIEnv *, jclass)
{
  return g_Info.Version;
}

JNIEXPORT jint JNICALL Java_org_terasology_TeraOVR_getHResolution
  (JNIEnv *, jclass)
{
  return g_Info.HResolution;
}

JNIEXPORT jint JNICALL Java_org_terasology_TeraOVR_getVResolution
  (JNIEnv *, jclass)
{
  return g_Info.VResolution;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getHScreenSize
  (JNIEnv *, jclass)
{
  return g_Info.HScreenSize;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getVScreenSize
  (JNIEnv *, jclass)
{
  return g_Info.VScreenSize;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getVScreenCenter
  (JNIEnv *, jclass)
{
  return g_Info.VScreenCenter;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getEyeToScreenDistance
  (JNIEnv *, jclass)
{
  return g_Info.EyeToScreenDistance;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getLensSeparationDistance
  (JNIEnv *, jclass)
{
  return g_Info.LensSeparationDistance;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getInterpupillaryDistance
  (JNIEnv *, jclass)
{
  return g_Info.InterpupillaryDistance;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getDistortitionK0
  (JNIEnv *, jclass)
{
  return g_Info.DistortionK[0];
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getDistortitionK1
  (JNIEnv *, jclass)
{
  return g_Info.DistortionK[1];
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getDistortitionK2
  (JNIEnv *, jclass)
{
  return g_Info.DistortionK[2];
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getDistortitionK3
  (JNIEnv *, jclass)
{
  return g_Info.DistortionK[3];
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getYaw
  (JNIEnv *, jclass)
{
  if (!g_Sensor) return 0.0f;

  Quatf quaternion = g_FusionResult.GetOrientation();
  float yaw, pitch, roll;

  quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

  return yaw;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getPitch
  (JNIEnv *, jclass)
{
  if (!g_Sensor) return 0.0f;

  Quatf quaternion = g_FusionResult.GetOrientation();
  float yaw, pitch, roll;

  quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

  return pitch;
}

JNIEXPORT jfloat JNICALL Java_org_terasology_TeraOVR_getRoll
  (JNIEnv *, jclass)
{
  if (!g_Sensor) return 0.0f;

  Quatf quaternion = g_FusionResult.GetOrientation();
  float yaw, pitch, roll;

  quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

  return pitch;
}

