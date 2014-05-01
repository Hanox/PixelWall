$(document).ready(function()
{
	addToHomescreen(
	{
		skipFirstVisit: false,	// show at first access
		startDelay: 0,          // display the message right away
		lifespan: 0,            // do not automatically kill the call out
		displayPace: 60,        // do not obey the display pace
		maxDisplayCount: 1      // do not obey the max display count
	});
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
var mSpacing = 2;
var mRefreshInterval = 1.0;
var mRefreshTimer;

//data
var mCurrentGridData;
var mCurrentTime;

var colorPalette = ["rgb(255,0,0)","rgb(0,255,0)","rgb(0,0,255)"];

/* Function definitions */
var fnUpdate = function()
{
    mRefreshTimer += mTime.deltaTime;
	if( mRefreshTimer > mRefreshInterval)
	{
		mRefreshTimer -= mRefreshInterval;
		getLatestData();
	}
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
            mCtx.fillRect( x*mPixelSize - mSpacing / 2, y*mPixelSize - mSpacing / 2, mPixelSize - mSpacing, mPixelSize - mSpacing);
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
	mRefreshTimer = 0.0;
	
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