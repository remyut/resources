package test.r.oboerecording;

import android.os.Environment;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Utils
{
    public static void writeToFile(String data, String fileName, String dirName)
    {
        //SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd-MM-yyyy-hh-mm-ss");
        //String timestamp = simpleDateFormat.format(new Date());

        //File dir = c.getFilesDir();

        File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS + "/" + dirName);
        //File file = new File(dir, fileName);
        if(!dir.exists())
            Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS).mkdirs();

        File file = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS + "/" + dirName), fileName);

        FileOutputStream stream = null;
        try
        {
            stream = new FileOutputStream(file);
            stream.write(data.getBytes());
            //Log.v("FLOW_TAG", "File with mX:" + file.getAbsolutePath());
        }
        catch (Exception e)
        {
            try {
                stream.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
        finally
        {
            try {
                stream.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}
