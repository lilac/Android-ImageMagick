package magick;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.magick.R;
import magick.util.DisplayImageMetaData;
import magick.util.MagickBitmap;

import android.util.Log;
import android.view.*;

public class AndroidMagickActivity extends Activity {
	static final int PROGRESS_DIALOG = 0;
	ProgressDialog progressDialog = null;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);
		// InputStream stream = getResources().openRawResource(R.raw.app_notes);
		
		
		try {
			final MagickImage img = new MagickImage(new ImageInfo(
					"/sdcard/1.jpg"));

			/*
			 * ImageView iv = new ImageView(this);
			 * iv.setImageBitmap(MagickBitmap.ToBitmap(img));
			 * setContentView(iv);
			 */
//			setContentView(R.layout.main);
			Spinner s = (Spinner) findViewById(R.id.spinner);
			ArrayAdapter adapter = ArrayAdapter.createFromResource(this,
					R.array.effects, android.R.layout.simple_spinner_item);
			adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
			s.setAdapter(adapter);
			
			s.setOnItemSelectedListener(new OnItemSelectedListener() {

				public void onItemSelected(AdapterView<?> parent, View view,
						int pos, long id) {
					ProgressThread t = new ProgressThread(img, pos);
					//runOnUiThread(t);
					t.run();
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
		
		/*
		 * TextView tv = new TextView(this);
		 * tv.setText(DisplayImageMetaData.displayMagickImage(img));
		 * setContentView(tv);
		 */
		int count = 3;
		MagickImage images[] = new MagickImage[count];
		for (int i = 0; i < count; i++) {
			String path = "/sdcard/" + String.valueOf(i + 1) + ".jpg";
			try {
				images[i] = new MagickImage(new ImageInfo(path));
			} catch (MagickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		try {
			MagickImage image = new MagickImage(images);
			image.setImageFormat("gif");
			String fn = Environment.getExternalStorageDirectory() + "/Pictures/test.gif";
			image.setFileName(fn);
			ImageInfo info = new ImageInfo(fn);
			info.setMagick("gif");
			//image.writeImage(info);
			byte blob[] = image.imageToBlob(info);
			FileOutputStream fos = new FileOutputStream(fn);
			fos.write(blob);
			fos.close();
			FileOutputStream testOS = new FileOutputStream("/mnt/sdcard/test.txt");
			testOS.write("abc".getBytes());
			testOS.close();
		} catch (MagickException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	protected Dialog onCreateDialog(int id, Bundle bundle) {
		switch (id) {
		case PROGRESS_DIALOG:
			/*
			 * ProgressDialog dialog =
			 * ProgressDialog.show(AndroidMagickActivity.this, "",
			 * "Loading. Please wait...", true);
			 */
			progressDialog = new ProgressDialog(AndroidMagickActivity.this);
			progressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			progressDialog.setMessage("Loading...");
			return progressDialog;
			// return dialog;
		default:
			return null;
		}
	}


	/** Nested class that performs progress calculations (counting) */
	private class ProgressThread extends Thread {
		
		MagickImage img;
		int pos;

		ProgressThread(MagickImage image, int pos) {
			this.img = image;
			this.pos = pos;
		}

		public void run() {
			int effect = 0;
			AndroidMagickActivity.this.showDialog(PROGRESS_DIALOG);
			switch (pos) {
			case 1:
				effect = NoiseType.UndefinedNoise;
				break;
			case 2:
				effect = NoiseType.UniformNoise;
				break;
			case 3:
				effect = NoiseType.GaussianNoise;
				break;
			case 4:
				effect = NoiseType.MultiplicativeGaussianNoise;
				break;
			case 5:
				effect = NoiseType.ImpulseNoise;
				break;
			case 6:
				effect = NoiseType.LaplacianNoise;
				break;
			case 7:
				effect = NoiseType.PoissonNoise;
				break;
			}
			Bitmap bitmap = null;
			try {
				ImageView iv = (ImageView) findViewById(R.id.imageView);

				MagickImage image = null;
				if (pos < 8)
					image = img.addNoiseImage(effect);
				else if (pos == 9)
					image = img.blurImage(5, 1);
				else if (pos == 10)
					image = img.charcoalImage(5, 1);
				else if (pos == 11)
					image = img.edgeImage(0);
				if (image != null) {

					bitmap = MagickBitmap.ToBitmap(image);
					iv.setImageBitmap(bitmap);
				}
				// bitmap.recycle(); we can't do that.
				AndroidMagickActivity.this.dismissDialog(PROGRESS_DIALOG);
			} catch (MagickException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}

	}

}
