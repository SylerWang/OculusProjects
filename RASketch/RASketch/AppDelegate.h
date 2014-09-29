//
//  AppDelegate.h
//  RASketch
//
//  Created by Rinat Abdrashitov on 2014-09-26.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RAGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet RAGLView *glView;

@end
