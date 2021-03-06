//
//  CouchChangeTracker.h
//  CouchCocoa
//
//  Created by Jens Alfke on 6/20/11.
//  Copyright 2011 Couchbase, Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
//  Unless required by applicable law or agreed to in writing, software distributed under the
//  License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
//  either express or implied. See the License for the specific language governing permissions
//  and limitations under the License.

#import <Foundation/Foundation.h>
@class CouchDatabase;


/** Reads the continuous-mode _changes feed of a database, and sends the individual lines to -[CouchDatabase receivedChangeChunk:].
    This class is used internally by CouchDatabase and you shouldn't need to use it yourself. */
@interface CouchChangeTracker : NSObject <NSStreamDelegate>
{
    @private
    CouchDatabase* _database;
    NSUInteger _lastSequenceNo;
    NSInputStream* _trackingInput;
    NSOutputStream* _trackingOutput;
    NSString* _trackingRequest;
    
    NSMutableData* _inputBuffer;
    int _state;
}

- (id)initWithDatabase: (CouchDatabase*)database sequenceNumber: (NSUInteger)lastSequenceNo;
- (BOOL) start;
- (void) stop;

@end
