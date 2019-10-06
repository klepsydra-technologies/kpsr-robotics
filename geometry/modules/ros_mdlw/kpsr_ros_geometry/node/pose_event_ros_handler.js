/**
 * This example demonstrates simple access to middleware ros through Klepsydra.
 */

'use strict';

function PoseEventHandler(rosnodejs) {
   var geometry_msgs_msgs = rosnodejs.require('geometry_msgs').msg;
   this.msgType = geometry_msgs_msgs.PoseStamped;
   this.from = function (data) { return data; };
   this.to = function (data) { return data; };
}

module.exports = PoseEventHandler;

