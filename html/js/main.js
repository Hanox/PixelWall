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

var mRefreshInterval = 5.0; //refresh every x seconds
var mRefreshTimer;
var mIndex;
var mLines;

//data
var mCurrentGridData;
var mCurrentTime;

var mFetching;

var colorPalette = ["rgb(255,0,0)","rgb(0,255,0)","rgb(0,0,255)"];

/* Function definitions */
var fnUpdate = function()
{
    mRefreshTimer += mTime.DeltaTime();
	if( mRefreshTimer > mRefreshInterval)
	{
		mRefreshTimer -= mRefreshInterval;
        
		if( !mFetching && ( mLines == null ||  (mLines != null && mIndex == mLines.length - 2) ) )
		{
			getData(-1);
		}
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
	
	var timeArr = mCurrentTime.split(" ");
	$("#date").text(timeArr[1] +" "+timeArr[2]);
	$("#year").text(timeArr[4]);
	
	var timeArrB = timeArr[3].split(":");
	$("#hours").text(timeArrB[0]);
	$("#minutes").text(timeArrB[1]);
	$("#seconds").text(timeArrB[2]);
}

function initApp()
{
    /* disable jQuery ajax caching to keep getting the latest file */
    $.ajaxSetup({cache: false});
    
	/* Size The Canvas */
	$("#canvas").attr("width", mGridWidth*mPixelSize+"px");
	$("#canvas").attr("height", mGridHeight*mPixelSize+"px");
	mCanvas = document.getElementById("canvas");
	mCtx = mCanvas.getContext("2d");
	
	/* Init time manager */
	mTime = new Time();
	mRefreshTimer = 0.0;
	mFetching = false;
    
	getData(-1);
	
	/* keyboard */
	document.addEventListener('keydown', function(event)
	{
		//LEFT
		if(event.keyCode == 37) { showPrev();}
		//RIGHT
		else if(event.keyCode == 39){ showNext(); }
	});
	
	/* buttons */
	$('#btn-prev').click(function () { showPrev(); });
	$('#btn-next').click(function () { showNext(); });

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

function getData(index)
{
	mIndex = index;
	if(mIndex == -1 )
	{
        mFetching = true;
		$("#status").css("background-color", "cyan");
		$.get('pixeldata.txt', function(data)
		{
			mLines = data.split("\n");
			tryUpdateGrid();
            mFetching = false;
			$("#status").css("background-color", "white");
		}, 'text');
	}
	else
	{
		tryUpdateGrid();
	}
}

function tryUpdateGrid()
{
	if(mIndex == -1 || mIndex > mLines.length - 2) mIndex = mLines.length - 2;
	var line = mLines[mIndex];
	var lineContents = line.split("|");
	mCurrentTime = lineContents[0];
	
	if(mCurrentGridData != lineContents[1])
	{
        mCurrentGridData = lineContents[1];
        drawGrid();
	}
}

function showNext() { getData(mIndex+1); }
function showPrev() { getData(mIndex-1); }