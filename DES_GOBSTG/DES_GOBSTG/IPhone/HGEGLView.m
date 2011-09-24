#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "HGEGLView.h"

#include "MainApplicationFunctions.h"

#define USE_DEPTH_BUFFER 0

// A class extension to declare private methods
@interface HGEGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *loopTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation HGEGLView

@synthesize context;
@synthesize loopTimer;
@synthesize loopInterval;

//
EAGLContext *context_cp = NULL;
/* OpenGL names for the renderbuffer and framebuffers used to render to this view */
GLuint viewRenderbuffer, viewFramebuffer;
/* The pixel dimensions of the backbuffer */
GLint backingWidth;
GLint backingHeight;


// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}



//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {
    
    if ((self = [super initWithCoder:coder])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        context_cp = context;
        loopInterval = 0;//1.0 / 60.0;
		
		for (int i=0; i<TOUCHPOINT_MAX; i++) {
			touchPoints[i] = NULL;
		}
		[[self window]setMultipleTouchEnabled:YES];
		[[super window]setMultipleTouchEnabled:YES];
    }
	
    return self;
}

- (BOOL) isMultipleTouchEnabled
{
	return YES;
};




void glCallFrameBuffer()
{	
    [EAGLContext setCurrentContext:context_cp];
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glViewport(0, 0, backingWidth,backingHeight);
}

void glCallRenderBuffer()
{
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context_cp presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (void)mainLoop {
    glCallFrameBuffer();
	Application_Loop();
	glCallRenderBuffer();
}


- (void)layoutSubviews {
	[EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
}


- (BOOL)createFramebuffer {
    
    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
    
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    return YES;
}


- (void)destroyFramebuffer {
    
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(depthRenderbuffer) {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}


- (void)startLoop {
    self.loopTimer = [NSTimer scheduledTimerWithTimeInterval:loopInterval target:self selector:@selector(mainLoop) userInfo:nil repeats:YES];
}


- (void)stopLoop {
    self.loopTimer = nil;
}


- (void)setLoopTimer:(NSTimer *)newTimer {
    [loopTimer invalidate];
    loopTimer = newTimer;
}


- (void)setLoopInterval:(NSTimeInterval)interval {
    
    loopInterval = interval;
    if (loopTimer) {
        [self stopLoop];
        [self startLoop];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event 
{
	int nAllTouches = [touches count];//[[event allTouches] count];
	for (int j=0; j<nAllTouches; j++) {
		UITouch *nowTouch = [[touches allObjects] objectAtIndex:j];//[[[event allTouches] allObjects] objectAtIndex:j];
		int i=0;
		
		bool tocontinue = false;
		for (; i<TOUCHPOINT_MAX; i++) {
			if (touchPoints[i] == nowTouch) {
				tocontinue = true;
				break;
			}
		}
		if (tocontinue) {
			continue;
		}
		UITouch *emptytouch = NULL;
		for (i=0; i<TOUCHPOINT_MAX; i++) {
			if (touchPoints[i] == NULL) {
				if (emptytouch == NULL) {
					touchPoints[i] = nowTouch;
					emptytouch = touchPoints[i];
					break;
				}
			}
		}
		if (emptytouch == NULL) {
			return;
		}
		if (i == TOUCHPOINT_MAX) {
			return;
		}
		CGPoint touchPoint = [emptytouch locationInView:self];
		TouchCallback_ButtonDown(touchPoint.x, touchPoint.y, i);
	}
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{
	int nAllTouches = [touches count];//[[event allTouches] count];
	for (int j=0; j<nAllTouches; j++) {
		int i=0;
		UITouch *movingtouch = [[touches allObjects]objectAtIndex:j];//[[[event allTouches] allObjects] objectAtIndex:j];
		
		for (; i<TOUCHPOINT_MAX; i++) {
			if (touchPoints[i] == movingtouch) {
				break;
			}
		}
		
		if (i == TOUCHPOINT_MAX) {
			return;
		}
		CGPoint touchPoint = [movingtouch locationInView:self];
		TouchCallback_Move(touchPoint.x, touchPoint.y, i);
	}
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	int nAllTouches = [touches count];//[[event allTouches] count];
	for (int j=0; j<nAllTouches; j++) {
		int i=0;
		UITouch *deletetouch = [[touches allObjects]objectAtIndex:j];//[[[event allTouches] allObjects] objectAtIndex:j];
		for (; i<TOUCHPOINT_MAX; i++) {
			if (touchPoints[i] == deletetouch) {
				touchPoints[i] = NULL;
				break;
			}
		}
		if (i == TOUCHPOINT_MAX) {
			return;
		}
		CGPoint touchPoint = [deletetouch locationInView:self];
		TouchCallback_ButtonUp(touchPoint.x, touchPoint.y, i);
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	int nAllTouches = [touches count];//[[event allTouches] count];
	int i=0;
	for (int j=0; j<nAllTouches; j++) {
		UITouch *deletetouch = [[touches allObjects]objectAtIndex:j];//[[[event allTouches] allObjects] objectAtIndex:j];
		for (; i<TOUCHPOINT_MAX; i++) {
			if (touchPoints[i] == deletetouch) {
				touchPoints[i] = NULL;
				break;
			}
		}
		CGPoint touchPoint = [deletetouch locationInView:self];
		TouchCallback_ButtonUp(touchPoint.x, touchPoint.y, i);
	}
}

- (void)dealloc {
    
    [self stopLoop];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [context release];  
    [super dealloc];
}

@end
