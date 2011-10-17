package magick;

//import android.R;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;
import android.magick.R;
import magick.util.DisplayImageMetaData;
import magick.util.MagickBitmap;

public class AndroidMagickActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.main);
        //InputStream stream = getResources().openRawResource(R.raw.app_notes);
        MagickImage img = null;
        try {
        	img = new MagickImage(new ImageInfo("/sdcard/images.jpeg"));
        	ImageView iv = new ImageView(this);
        	iv.setImageDrawable(new BitmapDrawable(getResources(), MagickBitmap.ToBitmap(img)));
        	setContentView(iv);
        } catch (MagickApiException e) {
        	e.printStackTrace();
        } catch (MagickException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*TextView tv = new TextView(this);
		tv.setText(DisplayImageMetaData.displayMagickImage(img));
		setContentView(tv);*/
        
        
    }
}