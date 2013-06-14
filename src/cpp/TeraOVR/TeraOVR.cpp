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

#include "OVR.h"
#include "jni.h"

#include <iostream>
#include <conio.h>

using namespace std;
using namespace OVR;

Ptr<DeviceManager>	pManager;
Ptr<HMDDevice>		pHMD;
Ptr<SensorDevice>	pSensor;
SensorFusion		FusionResult;
HMDInfo			Info;
bool			InfoLoaded;

void Init()
{
  System::Init();

  pManager = *DeviceManager::Create();

  pHMD = *pManager->EnumerateDevices<HMDDevice>().CreateDevice();

  if (pHMD)
  {
    InfoLoaded = pHMD->GetDeviceInfo(&Info);

    pSensor = *pHMD->GetSensor();
  }
  else
  {
    pSensor = *pManager->EnumerateDevices<SensorDevice>().CreateDevice();
  }

  if (pSensor)
  {
    FusionResult.AttachToSensor(pSensor);
  }
}

void Clear()
{
  pSensor.Clear();
  pHMD.Clear();
  pManager.Clear();

  System::Destroy();
}

void Output()
{
  cout << "----- Oculus Console -----" << endl;

  if (pHMD)
  {
    cout << " [x] HMD Found" << endl;
  }
  else
  {
    cout << " [ ] HMD Not Found" << endl;
  }

  if (pSensor)
  {
    cout << " [x] Sensor Found" << endl;
  }
  else
  {
    cout << " [ ] Sensor Not Found" << endl;
  }

  cout << "--------------------------" << endl;

  if (InfoLoaded)
  {
    cout << " DisplayDeviceName: " << Info.DisplayDeviceName << endl;
    cout << " ProductName: " << Info.ProductName << endl;
    cout << " Manufacturer: " << Info.Manufacturer << endl;
    cout << " Version: " << Info.Version << endl;
    cout << " HResolution: " << Info.HResolution<< endl;
    cout << " VResolution: " << Info.VResolution<< endl;
    cout << " HScreenSize: " << Info.HScreenSize<< endl;
    cout << " VScreenSize: " << Info.VScreenSize<< endl;
    cout << " VScreenCenter: " << Info.VScreenCenter<< endl;
    cout << " EyeToScreenDistance: " << Info.EyeToScreenDistance << endl;
    cout << " LensSeparationDistance: " << Info.LensSeparationDistance << endl;
    cout << " InterpupillaryDistance: " << Info.InterpupillaryDistance << endl;
    cout << " DistortionK[0]: " << Info.DistortionK[0] << endl;
    cout << " DistortionK[1]: " << Info.DistortionK[1] << endl;
    cout << " DistortionK[2]: " << Info.DistortionK[2] << endl;
    cout << " DistortionK[3]: " << Info.DistortionK[3] << endl;
    cout << "--------------------------" << endl;
  }

  cout << endl << " Press ENTER to continue" << endl;

  cin.get();

  while(pSensor)
  {
    Quatf quaternion = FusionResult.GetOrientation();

    float yaw, pitch, roll;
    quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

    cout << " Yaw: " << RadToDegree(yaw) << 
      ", Pitch: " << RadToDegree(pitch) << 
      ", Roll: " << RadToDegree(roll) << endl;

    Sleep(50);

    if (_kbhit()) exit(0);
  }
}

