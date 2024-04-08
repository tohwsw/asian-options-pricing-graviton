package main

import (
    "fmt"
    "log"
    "os/exec"
    "net/http"
    "encoding/json"
)

func pricingFunc(w http.ResponseWriter, r *http.Request){
    

    output, err := exec.Command("/bin/pricing").Output()
    if err!=nil {
        fmt.Println(err.Error())
    }
    //fmt.Println(string(output))

    resp := make(map[string]string)
    resp["price"] = string(output)
    jsonResp, err := json.Marshal(resp)
    if err != nil {
        log.Fatalf("Error happened in JSON marshal. Err: %s", err)
    }
    w.Header().Set("Content-Type", "application/json")
    w.Write(jsonResp)
    
}

func main() {
    http.HandleFunc("/pricing", pricingFunc)
    log.Fatal(http.ListenAndServe(":8080", nil))
}