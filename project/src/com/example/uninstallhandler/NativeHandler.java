package com.example.uninstallhandler;

public class NativeHandler {
	
	static{
		System.loadLibrary("sock");
	}
	public native int uninstall(String packageDir, int sdkVersion);
}
