#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#include "MainApplicationFunctions.h"

#include "Const.h"

@interface HGEGLView : UIView {
	
@public
	UITouch *touchPoints[TOUCHPOINT_MAX];
    
@private
       
    EAGLContext *context;
    
    GLuint depthRenderbuffer;
    
    NSTimer *loopTimer;
    NSTimeInterval loopInterval;
}

@property NSTimeInterval loopInterval;
- (void)startLoop;
- (void)stopLoop;
- (void)mainLoop;

@end
