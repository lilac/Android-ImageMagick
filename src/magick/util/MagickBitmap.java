package magick.util;

import java.awt.Dimension;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

import magick.ImageInfo;
import magick.MagickException;
import magick.MagickImage;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.os.Handler;
public class MagickBitmap {

	public static Bitmap ToBitmap(MagickImage img) throws MagickException {
		int width = img.getWidth();
		int height = img.getHeight();
		int count = width * height * 4;
		byte pixels[] = new byte[count];
		
		/* Because Java use big edian, when calling native bytesToInts, 
		 * we must reverse the order of ARGB. */
		boolean res = img.dispatchImage(0, 0, width, height, "BGRA", pixels);
		int colors[] = bytesToInts(pixels);
		//int colors[] = toIntArray(pixels);
		if (res) {
			return Bitmap.createBitmap(colors, width, height, Bitmap.Config.ARGB_8888);
		}
		else return null;
	}
	
	public static MagickImage fromBitmap(Bitmap bmp) throws MagickException {
		/*
		int width = bmp.getWidth();
		int height = bmp.getHeight();
		int count = width * height;
		int pixels[] = new int[count];
		bmp.getPixels(pixels, 0, width, 0, 0, width, height);*/
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		bmp.compress(CompressFormat.JPEG, 80, bos);
		ImageInfo info = new ImageInfo();
		info.setMagick("jpeg");
		MagickImage image = new MagickImage(info, bos.toByteArray());
		return image;
	}
	
	public static int[] toIntArray(byte[] barr) { 
        //Pad the size to multiple of 4 
        int size = (barr.length / 4) + ((barr.length % 4 == 0) ? 0 : 1);      

        ByteBuffer bb = ByteBuffer.allocate(size *4); 
        bb.put(barr); 

        //Java uses Big Endian. Network program uses Little Endian. 
        //bb.order(ByteOrder.LITTLE_ENDIAN); 
       

        int[] result = new int[size]; 
        bb.rewind(); 
        while (bb.remaining() > 0) { 
            result[bb.position()/4] =bb.getInt(); 
        } 

        return result; 
	}
	
	public native static int[] bytesToInts(byte[] bytes);
	
	static {
		System.loadLibrary("android-magick");
	}
}
