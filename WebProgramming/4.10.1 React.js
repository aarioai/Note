


 
class Rcc extends React.Component {
  static defaultProps = {
    autoPlay: false,
    initialCount: 10,
  }
  static propTypes = {
    autoPlay: React.PropTypes.bool.isRequired,
    initialCount: React.PropTypes.number.isRequired,
    posterFrameSrc: React.PropTypes.string.isRequired,
    videoSrc: React.PropTypes.string.isRequired,
  }
  state = {
    count: this.props.initialCount
  }
  /**
   *  comoponentWillMount: function(){
   *    
   *  }
   */
  constructor(props){
    super(props);
  }
  tick = (val, e) => {
    this.setState({
      count: this.state.count + 1,
      `${val}Sub`: e.target.value,   // ==>  arr[val + 'Sub'] = e.target.value
      });
  }
  tick(val, e){
    this.setState({count: this.state.count + 1});
  }
  render(){
    return (
      <div>
        {
          this.state.items.map(function(item, i){
            return (
              <div onClick={this.tick.bind(this, item)}></div>
              <div onClick={ancient.handleClick}></div>
            ); 
          }, this)     // bind this to child
        }
      </div>
    );
  }
} 
Rcc.propTypes = {initialCount: React.PropTypes.number};
Rcc.defaultProps = {initialCount: 0};