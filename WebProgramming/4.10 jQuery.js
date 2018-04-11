/** 
 * @see https://api.jquery.com/jQuery.ajax/ 
 */
$.ajax({
  method: 'GET', // PUT GET POST, same as type, but only support in 1.9+
  url: '',
  async:true,     // asynchronous, false on waiting for the ajax finished
  /**
   * 'applicaton/json'
   */
  contentType: 'application/x-www-form-urlencoded',
  accepts: '', // default depend on DataType
  dataType: 'json', // jsonp html xml script text
  data:{}     // or string
  dataFilter: function(data, type){},
  jsonp:
  jsonpCallback:function(){},
  
  /**
   *  headers: {name: 'lef'} is same as
   *  beforeSend: function(xml_http_request){
   *    xml_http_request.setRequestHeaders('name', 'lef');
   *  }
   */
  headers: {},
  
  cache:true,
  context: document.body,  // $(this)
  beforeSend(xhr, settings){},
  complete(xhr, text_status){},
  success:function(response){},
  error:function(xhr, text_status, error_thrown){},
  
  timeout: int,
  mimeType: '', 
  crossDomain: false,

  
  username: '',
  password: '',

  
  
  global:true,
  ifModified: false,
  isLocal: ,    //
  
  xhr: ActiveXObject,
  xhrFields: {}, 
})
