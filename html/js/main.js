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
var mPixelSize = 20;

var mCurrentGridData;
var mCurrentTime;
var colorPalette = ["rgb(255,0,0)","rgb(0,255,0)","rgb(0,0,255)"];

/* Function definitions */
var fnUpdate = function()
{
    
};

function drawGrid()
{
	for (var x=0;x<mGridWidth;++x)
    {
        for (var y=0;y<mGridHeight;++y)
        {
            // Find the starting index in the one-dimensional image data (we flip y)
            var i = (mGridHeight - y - 1) * mGridWidth + x;
            var colorIndex = parseInt(mCurrentGridData.substring(i,i+1));
            mCtx.fillStyle = colorPalette[colorIndex];
            mCtx.fillRect( x*mPixelSize, y*mPixelSize, mPixelSize, mPixelSize);
        }
    }
	$("#info").text(mCurrentTime);
}

function initApp()
{
	/* Size The Canvas */
	$("#canvas").attr("width", mGridWidth*mPixelSize+"px");
	$("#canvas").attr("height", mGridHeight*mPixelSize+"px");
	mCanvas = document.getElementById("canvas");
	mCtx = mCanvas.getContext("2d");
	
	/* Init time manager */
	mTime = new Time();
	
	getLatestData();

	/* Start the main loop */
	tick();
}

/* Main Timing Loop */
function tick()
{
    requestAnimFrame(tick);
	mTime.Tick();
	fnUpdate();
}

function getLatestData()
{
    $.get('pixeldata.txt', function(data)
    {
		var lines = data.split("\n");
		var line = lines[lines.length - 2];
		var lineContents = line.split("|");
		mCurrentTime = lineContents[0];
		
		if(mCurrentGridData != lineContents[1])
        {
          mCurrentGridData = lineContents[1];
          drawGrid();
        }
		
    }, 'text');
}