// Avoid `console` errors in browsers that lack a console.
(function() {
    var method;
    var noop = function () {};
    var methods = [
        'assert', 'clear', 'count', 'debug', 'dir', 'dirxml', 'error',
        'exception', 'group', 'groupCollapsed', 'groupEnd', 'info', 'log',
        'markTimeline', 'profile', 'profileEnd', 'table', 'time', 'timeEnd',
        'timeStamp', 'trace', 'warn'
    ];
    var length = methods.length;
    var console = (window.console = window.console || {});

    while (length--) {
        method = methods[length];

        // Only stub undefined methods.
        if (!console[method]) {
            console[method] = noop;
        }
    }
}());

// Place any jQuery/helper plugins in here.
/**
 * From WebGLUtils by Copyright 2010, Google Inc.
 * Provides requestAnimationFrame in a cross browser way.
 * Provides cancelRequestAnimationFrame in a cross browser way.
 */
window.requestAnimFrame = (function() {
  return window.requestAnimationFrame ||
         window.webkitRequestAnimationFrame ||
         window.mozRequestAnimationFrame ||
         window.oRequestAnimationFrame ||
         window.msRequestAnimationFrame ||
         function(/* function FrameRequestCallback */ callback, /* DOMElement Element */ element) {
           return window.setTimeout(callback, 1000/60);
         };
})();
window.cancelRequestAnimFrame = (function() {
  return window.cancelCancelRequestAnimationFrame ||
         window.webkitCancelRequestAnimationFrame ||
         window.mozCancelRequestAnimationFrame ||
         window.oCancelRequestAnimationFrame ||
         window.msCancelRequestAnimationFrame ||
         window.clearTimeout;
})();

/**
 * Timer Helper
 * by Hannes Devillé
 */
function Time()
{
	this.mLtime = null;
	this.mTOffset = 0;
	this.mTo = (new Date()).getTime(); //starting point for time to not exceed extreme values
	this.mFpsTime = 0;
	this.mFpsCount = 0;
	this.mDeltaTime = null;
	
	this.mFpsElem = document.getElementById("framerate");
	
	this.GetTime = function()
	{
		return this.mLtime/1000.0;
	}
	
	this.DeltaTime = function()
	{
		return this.mDeltaTime/1000.0;
	}

	this.Tick = function()
	{
		var currTime = (new Date()).getTime() - this.mTo;
		if(this.mLtime)
		{
			this.mDeltaTime = (currTime - this.mLtime);
			++this.mFpsCount;
			this.mFpsTime += this.mDeltaTime;
			if( this.mFpsTime>1000 )
			{
				this.mFpsTime -= 1000;
				
				/* Debug fps display */
				if(this.mFpsElem != null)
				{
					this.mFpsElem.innerHTML = this.mFpsCount + " fps";
				}
				
				this.mFpsCount = 0;
			}
		}
		this.mLtime = currTime;
	}
}