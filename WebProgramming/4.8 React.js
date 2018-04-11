/**
 * Using babel to compile jsx every time that you change it
 * @see http://facebook.github.io/react/docs/getting-started.html
 *  sh$ sudo npm install --global babel-cli
 *  sh$ sudo npm install babel-preset-react babel-preset-es2015
 *  sh$ babel --presets react <$source_file> --watch --out-dir <$build_to>
 *  sh$ babel --presets react src --watch --out-dir build
 */

 
 /**
  *
  */


/**
 * @see https://facebook.github.io/react/docs/tags-and-attributes.html
 */
/**
 * @warning distinguish the `this` is map
 * this.[state|prop].vars.map(function(item, i){}, hanle_this = each item);
 */
handle: function(){},
render: function(){
  var parent = this;
  return (
    <div>{
      this.state.items.map(function(item, i){
        var bound_handle = parent.handle.bind(item, i);    // notice `parent`
        return (
          <a href="javascript:void(0)" onClick=bound_handle>Aaron</a>
          <a href="javascript:void(0)" onClick=parent.handle>Script</a>
        );
      })
    }</div>
  );
}

render: function(){
  var list = this.props.items.map(function(item, i){
    var bound_handle = this.handle.bind(item, i);
    return (
      <a href="javascript:void(0)" onClick=bound_handle>Aaron</a>
      <a href="javascript:void(0)" onClick=this.handle>Script</a>
    );
  }, this);     // assign interior `this` to outter `this`
  return (
    <div>{list}</div>
  );
}




 
var Rcc = React.createClass({
  /**
   * Component Sepecifications
   * @see https://facebook.github.io/react/docs/component-specs.html
   *  getInitialState()
   *  propTypes()
   *  mixins
   * @see https://facebook.github.io/react/docs/reusable-components.html 
   */
  getInitialState: function(){},
  handleClick: function(item, e){
    this.setState({articleList:res.data});
    console.log(e.target); 
  },
  componentDidMount: function(){
    this.handleClick();
    //setInterval(this.handleClick, 30000);   // 轮询
  },
  render: function(){
    var ancient = this;
    return (
      <div>
        {
          this.state.items.map(function(item, i){
            return (
              <div onClick={ancient.handleClick.bind(this, item)}></div>
              <div onClick={ancient.handleClick}></div>
            ); 
          }, this)     // bind this to child
        }
      </div>
    );
  }
});
