/**
 * @author AarioAi@gmail.com
 */
package docker

import (
	"log"
	"github.com/go-yaml/yaml"
	"io/ioutil"
	"strconv"
)

type DockerRunStruct struct {
	Container_name string

	Restart       string
	Privileged    string
	Ulimits       []string
	Cpu_shares    string
	Cpuset        string
	Cap_add       []string
	Cap_drop      []string
	Net           string
	Dns           []string
	Dns_search    []string
	Ipc           string
	Mem_limit     string
	Memswap_limit string
	Stdin_open    string
	Tty           string

	Links          []string
	External_links []string
	Volumes        []string
	Volumes_from   []string
	Read_only      string

	Build       string
	Pid         string
	Ports       []string
	Expose      []string
	Working_dir string
	Entrypoint  string
	Command     []string
	User        string
	Hostname    string
	Domainname  string
	Mac_address string
	Log_driver  string
	Log_opt     []string
	Environment []string
	Env_file    []string
	Extends     []string
}

func parseYaml(filename string) map[interface{}]interface{} {
	data, _ := ioutil.ReadFile(filename)
	m := make(map[interface{}]interface{})
	err := yaml.Unmarshal([]byte(data), &m)
	if err != nil {
		log.Fatalf("error: %v", err)
	}
	return m
}

func toArr(d interface{}) (a []string, ok bool) {
	//fmt.Println(reflect.TypeOf(d))
	switch d.(type) {
	case int:
		s := 0
		if s, ok = d.(int); ok {
			a = []string{strconv.Itoa(s)}
			return a, ok
		}
	case string:
		s := ""
		if s, ok = d.(string); ok {
			a = []string{s}
			return a, ok
		}
	case []int, []string, []interface{}:
		var u = d.([]interface{})
		l := len(u)
		a = make([]string, l)
		ok = false
		for k, v := range u {
			if a[k], ok = v.(string); !ok {
				a[k] = strconv.Itoa(v.(int))
			}
			ok = true
		}
		return a, ok
	}
	return []string{}, false
}

func dockerRunArgs(conf map[interface{}]interface{}, shared map[interface{}]interface{}) DockerRunStruct {
	r := DockerRunStruct{}
	ok := false

	r.Restart, _ = conf["restart"].(string)
	if r.Restart == "" {
		if r.Restart, ok = shared["restart"].(string); !ok {
			r.Restart = "always"
		}
	}
	r.Privileged, _ = conf["privileged"].(string)
	if r.Privileged == "" {
		r.Privileged, ok = shared["privileged"].(string)
	}
	r.Ulimits, _ = toArr(conf["ulimits"])
	if len(r.Ulimits) == 0 {
		r.Ulimits, _ = toArr(shared["ulimits"])
	}
	r.Cpu_shares, _ = conf["cpu_shares"].(string)
	if len(r.Cpu_shares) == 0 {
		r.Cpu_shares, _ = shared["cpu_shares"].(string)
	}
	r.Cpuset, _ = conf["cpuset"].(string)
	if len(r.Cpuset) == 0 {
		r.Cpuset, _ = shared["cpuset"].(string)
	}
	r.Cap_add, _ = toArr(conf["cap_add"])
	if len(r.Cap_add) == 0 {
		r.Cap_add, _ = toArr(shared["cap_add"])
	}
	r.Cap_drop, _ = toArr(conf["cap_drop"])
	if len(r.Cap_drop) == 0 {
		r.Cap_drop, _ = toArr(shared["cap_drop"])
	}
	r.Net, _ = conf["net"].(string)
	if r.Net == "" {
		r.Net, ok = shared["net"].(string)
	}
	r.Dns, _ = toArr(conf["dns"])
	if len(r.Dns) == 0 {
		r.Dns, _ = toArr(shared["dns"])
	}
	r.Dns_search, _ = toArr(conf["dns_search"])
	if len(r.Dns_search) == 0 {
		r.Dns_search, _ = toArr(shared["dns_search"])
	}
	r.Ipc, _ = conf["ipc"].(string)
	if r.Ipc == "" {
		r.Ipc, ok = shared["ipc"].(string)
	}
	r.Mem_limit, _ = conf["mem_limit"].(string)
	if r.Mem_limit == "" {
		r.Mem_limit, ok = shared["mem_limit"].(string)
	}
	r.Memswap_limit, _ = conf["memswap_limit"].(string)
	if r.Memswap_limit == "" {
		r.Memswap_limit, ok = shared["memswap_limit"].(string)
	}
	r.Stdin_open, _ = conf["stdin_open"].(string)
	if r.Stdin_open == "" {
		r.Stdin_open, ok = shared["stdin_open"].(string)
	}
	r.Tty, _ = conf["tty"].(string)
	if r.Tty == "" {
		r.Tty, ok = shared["tty"].(string)
	}

	r.Links, _ = toArr(conf["links"])
	if len(r.Links) == 0 {
		r.Links, _ = toArr(shared["links"])
	}
	r.External_links, _ = toArr(conf["external_links"])
	if len(r.External_links) == 0 {
		r.External_links, _ = toArr(shared["external_links"])
	}
	r.Volumes, _ = toArr(conf["volumes"])
	if len(r.Volumes) == 0 {
		r.Volumes, _ = toArr(shared["volumes"])
	}
	r.Volumes_from, _ = toArr(conf["volumes_from"])
	if len(r.Volumes_from) == 0 {
		r.Volumes_from, _ = toArr(shared["volumes_from"])
	}
	r.Read_only, _ = conf["read_only"].(string)
	if r.Read_only == "" {
		r.Read_only, ok = shared["read_only"].(string)
	}

	r.Build, _ = conf["build"].(string)
	r.Pid, _ = conf["pid"].(string)
	r.Ports, ok = toArr(conf["ports"])
	r.Expose, _ = toArr(conf["pxpose"])
	r.Working_dir, _ = conf["porking_dir"].(string)
	r.Entrypoint, _ = conf["entrypoint"].(string)
	r.Command, _ = toArr(conf["command"])
	r.User, _ = conf["user"].(string)
	r.Hostname, _ = conf["hostname"].(string)
	r.Domainname, _ = conf["domainname"].(string)
	r.Mac_address, _ = conf["mac_address"].(string)
	r.Log_driver, _ = conf["log_driver"].(string)
	r.Log_opt, _ = toArr(conf["log_opt"])
	r.Environment, _ = toArr(conf["environment"])
	r.Env_file, _ = toArr(conf["env_file"])
	r.Extends, _ = toArr(conf["extends"])

	return r
}
func handleSeq(seq *[]string, rs map[string]DockerRunStruct, name string) {
	if name == "" {
		return
	}
	for _, n := range *seq {
		if name == n {
			return
		}
	}
	links := rs[name].Links
	for _, link := range links {
		handleSeq(seq, rs, link)
	}
	*seq = append((*seq), name)
}
func compose(filename string) (rs map[string]DockerRunStruct, seq []string) {
	yaml := parseYaml(filename)
	var services map[interface{}]interface{}
	var shared map[interface{}]interface{}
	if _, ok := yaml["services"]; ok {
		services = yaml["services"].(map[interface{}]interface{})
		shared = yaml
	} else {
		services = yaml
	}

	l := len(services)
	rs = make(map[string]DockerRunStruct, l)
	seq = make([]string, 0)

	for name, conf := range services {
		b := dockerRunArgs(conf.(map[interface{}]interface{}), shared)
		b.Container_name = name.(string)
		rs[name.(string)] = b
	}

	for name, _ := range rs {
		handleSeq(&seq, rs, name)
	}
	return rs, seq
}

func ComposeCmds(filename string) (cmds []string) {
	_, seq := compose(filename)
	l := len(seq)
	cmds = make([]string, l)
	for i := 0; i < l; i++ {
		cmd := "--------secret-------"
		cmds = append(cmds, cmd)
	}
	return cmds
}
