package test.r.myapplication.threading;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class WorkerThread implements Runnable
{
    private String command;
    private Handler callback;

    public WorkerThread(String s, Handler _callback){
        this.command=s;
        callback = _callback;
    }

    @Override
    public void run() {
        Log.d("CALLBACK", Thread.currentThread().getName()+" Start. Command = "+command);
        processCommand();
        Log.d("CALLBACK", Thread.currentThread().getName()+" End.");
    }

    private void processCommand() {
        try {
            Thread.sleep(5000);
            jobDone();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String toString(){
        return this.command;
    }

    public void jobDone()
    {
        Log.d("CALLBACK", "JOB DONE");
        //Message msg = uiHandler.obtainMessage(10, new Note(strNote));
        Message msg = callback.obtainMessage(10, command + "is DONE");
        msg.sendToTarget();
    }
}
