//
//  RAGLView.h
//  RASketch
//
//  Created by Rinat Abdrashitov on 2014-09-26.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface RAGLView : NSOpenGLView

//-(id)initWithCoder:(NSCoder *)aDecoder;
-(void)drawRect:(NSRect)dirtyRect;
-(void)prepareOpenGL;
-(void)reshape;

@end
