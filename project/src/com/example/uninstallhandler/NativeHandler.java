package com.example.uninstallhandler;

public class NativeHandler {
	
	static{
		System.loadLibrary("test");
	}
	public native int uninstall(String packageDir, int sdkVersion);
}
