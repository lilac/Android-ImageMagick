package magick;

//import android.R;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.magick.R;
import magick.util.DisplayImageMetaData;
import magick.util.MagickBitmap;

import android.view.*;

public class AndroidMagickActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.main);
        //InputStream stream = getResources().openRawResource(R.raw.app_notes);
        try {
        	final MagickImage img = new MagickImage(new ImageInfo("/sdcard/images.jpeg"));
        	/*
        	ImageView iv = new ImageView(this);
        	iv.setImageDrawable(new BitmapDrawable(getResources(), MagickBitmap.ToBitmap(img)));
        	setContentView(iv);
        	*/
        	setContentView(R.layout.main);

            Spinner s = (Spinner) findViewById(R.id.spinner);
            ArrayAdapter adapter = ArrayAdapter.createFromResource(
                    this, R.array.effects, android.R.layout.simple_spinner_item);
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            s.setAdapter(adapter);
            s.setOnItemSelectedListener(new OnItemSelectedListener() {

                public void onItemSelected(AdapterView<?> parent,
                		View view, int pos, long id) {
                	/*
                  Toast.makeText(parent.getContext(), "The planet is " +
                      parent.getItemAtPosition(pos).toString(), Toast.LENGTH_LONG).show();
                	 */
                	String item = parent.getSelectedItem().toString();
                	int effect = 0;
                	if (item.equals("Uniform Noise")) effect = NoiseType.UniformNoise;
                	else if (item.equals("Gaussian Noise")) effect = NoiseType.GaussianNoise;
                	Bitmap bitmap;
					try {
						bitmap = MagickBitmap.ToBitmap(img.addNoiseImage(effect));
						ImageView iv = (ImageView) findViewById(R.id.imageView);
                	iv.setImageBitmap(bitmap);
					} catch (MagickException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
                	
                }

                public void onNothingSelected(AdapterView<?> parent) {
                  // Do nothing.
                }
            });
            ImageView iv = (ImageView) findViewById(R.id.imageView);
            iv.setImageBitmap(MagickBitmap.ToBitmap(img));
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