package com.unity.imgui;

import androidx.appcompat.app.AppCompatActivity;
import android.os.*;
import android.util.Log;
import android.content.Context;
import android.widget.Toast;
import com.unity.imgui.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

	private ActivityMainBinding binding;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
		// Remove this line if you don't want AndroidIDE to show this app's logs
		super.onCreate(savedInstanceState);
        // Inflate and get instance of binding
		binding = ActivityMainBinding.inflate(getLayoutInflater());
        // set content view to binding's root
        setContentView(binding.getRoot());
    }
}
