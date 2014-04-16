$(document).ready(function(){
	initApp();
});

var mCanvas;
var mCtx;

/* Grid */
var mShowGrid = true;
var mRedrawRequested = true;
var mGridWidth = 30;
var mGridHeight = 20;
var mPixelSize = 32;

var mCurrentGridData;
var colorPalette = ["rgb(255,0,0)","rgb(0,255,0)","rgb(0,0,255)"];

/* Function definitions */
var fnUpdate = function() {};
var fnDraw = function() {};

var fnDrawGrid = function()
{
	if(mShowGrid && mRedrawRequested)
	{
		mRedrawRequested = false;

		for (var x=0;x<mGridWidth;++x)
		{
			for (var y=0;y<mGridHeight;++y)
			{
		    	// Find the starting index in the one-dimensional image data
				var i = y*mGridWidth + x;
				/*
				var r = imgData[i];
				*/
				
				var colorIndex = parseInt(mCurrentGridData.substring(i,i+1));
				
				mCtx.fillStyle = colorPalette[colorIndex];
				mCtx.fillRect( x*mPixelSize, y*mPixelSize, mPixelSize, mPixelSize);
			}
		}
	}
};

function initApp(){
	/* Size The Canvas */
	$("#canvas").attr("width", mGridWidth*mPixelSize+"px");
	$("#canvas").attr("height", mGridHeight*mPixelSize+"px");
	mCanvas = document.getElementById("canvas");
	mCtx = mCanvas.getContext("2d");
	
	/* Init time manager */
	mTime = new Time();
	
	$.get('pixeldata.txt', function(data)
	{
		mCurrentGridData = data;
		
		/* start drawing the grid */
		fnDraw = fnDrawGrid;
	}, 'text');

	/* Start the main loop */
	tick();
}

/* Main Timing Loop */
function tick()
{
    requestAnimFrame(tick);
	mTime.Tick();
	fnUpdate();
	drawScene();
}

function drawScene()
{
	fnDraw();
}