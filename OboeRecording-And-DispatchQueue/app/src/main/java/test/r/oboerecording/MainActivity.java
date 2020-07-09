package test.r.oboerecording;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity
        implements ActivityCompat.OnRequestPermissionsResultCallback
{
    private static final String TAG = MainActivity.class.getName();
    private static final int AUDIO_EFFECT_REQUEST = 0;

    private Button startEngineButton, stopEngineButton, startRecordingButton, stopRecordingButton, RawSignal;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startRecordingButton = findViewById(R.id.startRecording);
        startRecordingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startRecording();
            }
        });
        startRecordingButton.setText(getString(R.string.start_recording));

        ////

        stopRecordingButton = findViewById(R.id.stopRecording);
        stopRecordingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                stopRecording();
            }
        });
        stopRecordingButton.setText(getString(R.string.stop_recording));

        startEngineButton = findViewById(R.id.startEngine);
        startEngineButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                RecordingEngine.startEngine();
            }
        });
        startEngineButton.setText(getString(R.string.start_engine));

        stopEngineButton = findViewById(R.id.stopEngine);
        stopEngineButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                RecordingEngine.stopEngine();
            }
        });
        stopEngineButton.setText(getString(R.string.stop_engine));

        //Export to file - rawSignal + other processing
        RawSignal = findViewById(R.id.exportToFile);
        RawSignal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Recorded data
                String s = RecordingEngine.getRecordedData();
                Log.d("DATA %s", s);
                Utils.writeToFile(s, "recordedData.data", "Native");

                //normalized window
                String s1 = RecordingEngine.getNormalizedWindow();
                Log.d("DATA %s", s1);
                Utils.writeToFile(s1, "normalizedWindow.data", "Native");

                //signal sample - extract
                String s2 = RecordingEngine.getExtract();
                Log.d("DATA %s", s2);
                Utils.writeToFile(s2, "signalExtract.data", "Native");

                //windowed signal
                String s3 = RecordingEngine.getWindowedSignal();
                Log.d("DATA %s", s3);
                Utils.writeToFile(s3, "windowedSignal.data", "Native");

                //FFT Buffer
                String s4 = RecordingEngine.getFFTbuffer();
                Log.d("DATA %s", s4);
                Utils.writeToFile(s4, "fftBuffer.data", "Native");

                //Sectrum
                String s5 = RecordingEngine.getSpectrum();
                Log.d("DATA %s", s5);
                Utils.writeToFile(s5, "spectrum.data", "Native");

                //HPS Result
                String s6 = RecordingEngine.getHPSResult();
                Log.d("DATA %s", s6);
                Utils.writeToFile(s6, "hpsRes.data", "Native");


            }
        });

        RawSignal.setText(getString(R.string.export_signals));
    }

    @Override
    public void onResume(){
        // Check we have the record permission
        if (isRecordPermissionGranted()){
            //RecordingEngine.startEngine();
        } else {
            Log.d(TAG, "Requesting recording permission");
            requestRecordPermission();
        }
        super.onResume();
    }

    @Override
    public void onPause() {
        //RecordingEngine.stopEngine();
        super.onPause();
    }

    private void startRecording() {
        Log.d(TAG, "Attempting to start");

        if (!isRecordPermissionGranted()){
            requestRecordPermission();
            return;
        }
        RecordingEngine.setRecording(true);
    }

    private void stopRecording() {
        Log.d(TAG, "Playing, attempting to stop");
        RecordingEngine.setRecording(false);
    }

    private boolean isRecordPermissionGranted() {
        boolean isOk = false;

        isOk = ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) ==
                PackageManager.PERMISSION_GRANTED;

        isOk = ActivityCompat.checkSelfPermission(this,
                Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;

        return isOk;
    }

    private void requestRecordPermission(){
        ActivityCompat.requestPermissions(
                this,
                new String[]{Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE},
                AUDIO_EFFECT_REQUEST);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults)
    {

        if (AUDIO_EFFECT_REQUEST != requestCode) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
            return;
        }

        if (grantResults.length != 1 ||
                grantResults[0] != PackageManager.PERMISSION_GRANTED) {

            // User denied the permission, without this we cannot record audio
            // Show a toast and update the status accordingly
            //statusText.setText(R.string.status_record_audio_denied);
            Toast.makeText(getApplicationContext(),
                    getString(R.string.need_record_audio_permission),
                    Toast.LENGTH_SHORT)
                    .show();
        } else {
            // Permission was granted, start live effect
            //toggleEffect();
        }

    }
}

