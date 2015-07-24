package com.example.uninstallhandler;

public class NativeHandler {
	
	static{
		System.loadLibrary("test");
	}
	public native void uninstall(String packageDir, int sdkVersion);
}
