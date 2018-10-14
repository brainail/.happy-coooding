module.exports = LinkedList_2_3 = (function() {
  var deleteNode = function(node) {
    if(!node || !node.next) return;
    var next = node.next;
    node.data = next.data
    node.next = next.next;
  };

  return {
    deleteNode: deleteNode
  }
}());
