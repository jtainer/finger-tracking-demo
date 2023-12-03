#!/bin/bash
rm src/*
rm inc/*
rm lib/usb/*
cp ~/STM32CubeIDE/workspace_1.11.0/finger-tracking-demo/Core/Src/* src/
cp ~/STM32CubeIDE/workspace_1.11.0/finger-tracking-demo/Core/Inc/* inc/
cp ~/STM32CubeIDE/workspace_1.11.0/finger-tracking-demo/USB_DEVICE/App/* lib/usb/
cp ~/STM32CubeIDE/workspace_1.11.0/finger-tracking-demo/USB_DEVICE/Target/* lib/usb/


