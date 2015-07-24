package com.example.uninstallhandler;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		new NativeHandler().uninstall("/data/data/"+getPackageName(), android.os.Build.VERSION.SDK_INT);
	}
}
