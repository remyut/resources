package test.r.myapplication.threading;

import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import test.r.myapplication.R;

public class HandlerCallback implements Handler.Callback
{
    private EditText history;

    public HandlerCallback(View _v)
    {
        history = _v.findViewById(R.id.history);
    }

    @Override
    public boolean handleMessage(Message msg)
    {
        Log.d("CALLBACK", "Handler callback");
        if (msg.what == 10)
        {
            String str = (String) msg.obj;
            Log.d("CALLBACK", "Get message OK" + str);
            history.setText("GET Message OK" + str);
            return true;
        }
        return false;
    }
}
