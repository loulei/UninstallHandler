package com.example.uninstallhandler;

import java.io.File;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		File file = getDir("test", Context.MODE_PRIVATE);
		System.out.println(file.getPath());
		int pid = new NativeHandler().uninstall("/data/data/"+getPackageName(), android.os.Build.VERSION.SDK_INT);
		System.out.println("pid from native:"+pid);
	}
}
