package org.diracvideo.Schroedinger;

public class VideoFormat {
    public int index;
    public int width, height;
    public int chroma_format;
    
    public boolean interlaced, top_field_first;
    public int frame_rate_numerator, frame_rate_denominator,
	aspect_ratio_numerator, aspect_ratio_denominator;
    public int clean_width, clean_height, left_offset, top_offset;
    public int luma_offset, luma_excursion, chroma_offset, chroma_excursion;
    public int interlaced_coding;
    
    private static int[][] defaultFormats = {
	{ 0, 640, 480, 0420, 0, 0, 24000, 1001, /*custom */
	  1, 1, 640, 480, 0, 0, 0, 255, 128, 255, 0, 0, 0 },
	{ 1,  176, 120, 0420,0,0, 15000, 1001, 10, /* QSIF525 */
	   11, 176, 120, 0, 0, 0, 255, 128, 255, 1, 1, 0 },
	{ 2, 176, 144, 0420, 0, 1, 25, 2, 12, 11, /* QCIF */
	  176, 144, 0, 0, 0, 255, 128, 255, 2, 1, 0 },
	{ 3, 352, 240, 0420, 0, 0, 15000, 1001, 10, /* SIF525 */
	  11, 352, 240, 0, 0,   0, 255, 128, 255, 1, 1, 0 },
	{ 4, 352, 288, 0420, 0, 1, 25, 2, 12, 11,  /* CIF */
	  352, 288, 0, 0, 0, 255, 128, 255, 2, 1, 0 },
	{ 5, 704, 480, 0420, 0, 0, 15000, 1001, 10, /* 4SIF525 */
	  11, 704, 480, 0, 0, 0, 255, 128, 255, 1, 1, 0 },
	{ 6, 704, 576, 0420, 0, 1, 25, 2, 12, 11, /* 4CIF */
	  704, 576, 0, 0, 0, 255, 128, 255, 2, 1, 0 },
	{ 7, 720, 480, 0422,  1, 0,  30000, 1001, 10, 11, /* SD480I-60 */
	  704, 480, 8, 0, 64, 876, 512, 896, 1, 1, 0 },
	{ 8, 720, 576, 0422, 1, 1, 25, 1, 12, 11, 704, 576, /* SD576I-50 */
	  8, 0, 64, 876, 512, 896, 2, 1, 0 },
	{ 9, 1280, 720, 0422, 0, 1, 60000, 1001, 1, 1, /* HD720P-60 */
	  1280, 720, 0, 0, 64, 876, 512, 896, 0, 0, 0 },
	{ 10, 1280, 720, 0422, 0, 1, 50, 1, 1, 1, /* HD720P-50 */
	  1280, 720, 0, 0, 64, 876, 512, 896, 0, 0, 0 },
	{ 11, 1920, 1080, 0422, 1, 1,30000, 1001, 1, 1, /* HD1080I-60 */
	  1920, 1080, 0, 0, 64, 876, 512, 896,  0, 0, 0 },
	{ 12, 1920, 1080, 0422, 1, 1, 25, 1, 1, 1, /* HD1080I-50 */
	  1920, 1080, 0, 0, 64, 876, 512, 896, 0, 0, 0 },
	{ 13, 1920, 1080, 0422, 0, 1, 60000, 1001, 1, 1, /* HD1080P-60 */
	  1920, 1080, 0, 0, 64, 876, 512, 896, 0, 0, 0 },
	{ 14, 1920, 1080, 0422, 0, 1, 50, 1, 1, 1, /* HD1080P-50 */
	  1920, 1080, 0, 0, 64, 876, 512, 896,  0, 0, 0 },
	{ 15, 2048, 1080, 0444, 0, 1, 24, 1, 1, 1, /* DC2K */
	  2048, 1080, 0, 0, 256, 3504, 2048, 3584, 3, 0, 0 },
	{ 16, 4096, 2160, 0444, 0, 1, 24, 1, 1, 1, /* DC4K */
	  2048, 1536, 0, 0, 256, 3504, 2048, 3584,  3, 0, 0 }
    };

    private static int [][] defaultFrameRates = {
	{ 0, 0 }, { 24000, 1001 },
	{ 24, 1 }, { 25, 1 },
	{ 30000, 1001 }, { 30, 1 }, 
        { 50, 1 }, { 60000, 1001 },
        { 60, 1 },  { 15000, 1001 }, { 25, 2 }
    };
    
    private static int [][] defaultAspectRatios = {
	{ 0, 0 }, { 1, 1 },
        { 10, 11 }, { 12, 11 },
        { 40, 33 }, { 16, 11 },  { 4, 3 }
    };

    private static int [][] defaultSignalRanges = {
	{ 0, 0, 0, 0 },
	{ 0, 255, 128, 255 },
	{ 16, 219, 128, 224 },
	{ 64, 876, 512, 896, },
	{ 256, 3504, 2048, 3584 }
    };


    private void setDefaultVideoFormat(int i) throws Exception {
	if (i >= VideoFormat.defaultFormats.length) {
	    throw new Exception("Unsupported Video Format");
	}
	int a[] = VideoFormat.defaultFormats[i];
	this.index = a[0];
	this.width = a[1];
	this.height = a[2];
	this.chroma_format = a[3];
	this.interlaced = ( a[4] == 0 ? false : true);
	this.top_field_first = (a[5] == 0 ? false : true);
	this.frame_rate_numerator = a[6];
	this.frame_rate_denominator = a[7];
	this.aspect_ratio_numerator = a[8];
	this.aspect_ratio_denominator = a[9];
	this.clean_width = a[10];
	this.clean_height = a[11];
	this.left_offset = a[12];
	this.top_offset = a[13];
	this.luma_offset = a[14];
	this.luma_excursion = a[15];
	this.chroma_offset = a[16];
	this.chroma_offset = a[17];
    }

    private void setDefaultFrameRate(int i) throws Exception {
	if(i >= VideoFormat.defaultFrameRates.length) {
	    throw new Exception("Unsuported Frame Rate");
	}
	int a[] = VideoFormat.defaultFrameRates[i];
	this.frame_rate_numerator = a[0];
	this.frame_rate_denominator = a[1];
    }

    private void setDefaultAspectRatio(int i) throws Exception {
	if(i >= VideoFormat.defaultAspectRatios.length) {
	    throw new Exception("Unsupported Aspect Ratio");
	}
	int a[] = VideoFormat.defaultAspectRatios[i];
	this.aspect_ratio_numerator = a[0];
	this.aspect_ratio_denominator = a[1];
    }

    private void setDefaultSignalRange(int i) throws Exception {
	if (i >= VideoFormat.defaultSignalRanges.length) {
	    throw new Exception("Unsupported Signal Range");
	}
	int a[] = VideoFormat.defaultSignalRanges[i];
	this.luma_offset = a[0];
	this.luma_excursion = a[1];
	this.chroma_offset = a[2];
	this.chroma_excursion = a[3];
    }

    private void setDefaultColourSpec(int i) {
	
    }

    public VideoFormat(Unpack u) throws Exception {
	setDefaultVideoFormat(u.decodeUint());
	if(u.decodeBool()) { /* frame dimensions */
	    this.width = u.decodeUint();
	    this.height = u.decodeUint();
	}
	if(u.decodeBool()) { /* chroma format */
	    int c = u.decodeUint();
	}

	if(u.decodeBool()) { /* scan format */
	    this.interlaced = u.decodeBool();
	    if(this.interlaced) {
		this.top_field_first = u.decodeBool();
	    }
	}

	if(u.decodeBool()) { /* frame rate */
	    int i = u.decodeUint();
	    if(i == 0) {
		this.frame_rate_numerator = u.decodeUint();
		this.frame_rate_denominator = u.decodeUint();
	    } else {
		setDefaultFrameRate(i);
	    }
	}

	if(u.decodeBool()) { /* aspect ratio */
	    int i = u.decodeUint();
	    if(i == 0) {
		this.aspect_ratio_numerator = u.decodeUint();
		this.aspect_ratio_denominator = u.decodeUint();
	    } else {
		setDefaultAspectRatio(i);
	    }
	}
	
	if(u.decodeBool()) { /* clean area */
	    this.clean_width = u.decodeUint();
	    this.clean_height = u.decodeUint();
	    this.left_offset = u.decodeUint();
	    this.top_offset = u.decodeUint();
	}
	
	if(u.decodeBool()) { /* signal range */
	    int i = u.decodeUint();
	    if(i == 0) {
		this.luma_offset = u.decodeUint();
		this.luma_excursion = u.decodeUint();
		this.chroma_offset = u.decodeUint();
		this.chroma_excursion = u.decodeUint();
	    } else {
		setDefaultSignalRange(i);
	    }
	}

	if(u.decodeBool()) { /* colour spec */
	    int i = u.decodeUint();
	    setDefaultColourSpec(i);
	    if(i == 0) {
		if(u.decodeBool()) {
		    u.decodeUint();
		}
		if(u.decodeBool()) {
		    u.decodeUint();
		}
		if(u.decodeBool()) {
		    u.decodeUint();
		}
	    }
	}
	
	this.interlaced_coding = u.decodeUint();
	validate();
    }

    private void validate() {
	if(0 == this.aspect_ratio_numerator) {
	    this.aspect_ratio_numerator = 1;
	}
	if(0 == this.aspect_ratio_denominator) {
	    this.aspect_ratio_denominator = 1;
	}
	int max = java.lang.Math.max(this.chroma_excursion,
				   this.luma_excursion);
	if(max > 255 || max < 128) {
	    /* well, now what? */
	}
	
    }
}
