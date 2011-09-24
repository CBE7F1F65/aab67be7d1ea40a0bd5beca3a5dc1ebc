//
//  DES_GOBSTGAppDelegate.h
//  DES_GOBSTG
//
//  Created by h5nc on 10-10-11.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@class HGEGLView;

@interface DES_GOBSTGAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    HGEGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet HGEGLView *glView;

@end

