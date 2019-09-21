<template>
  <div id="app">
    <el-container>
      <el-header>
        <Header></Header>
      </el-header>
      <el-container>
        <el-aside>
          <Aside></Aside>
        </el-aside>
        <el-container>
          <el-main>
            
          </el-main>
          <el-footer>
            <Footer></Footer>
          </el-footer>
        </el-container>
      </el-container>
    </el-container>
  </div>
</template>

<script>
import Header from "./components/Header/Header";
import Footer from "./components/Footer/Footer";
import Aside from "./components/Aside/Aside";
export default {
  name: "App",
  components: {
    Header,
    Aside,
    Footer
  }
};
</script>

<style>
body {
  margin: 0 0;
  height: 100%;
}
.el-header {
  padding: 0;
  width: 100%;
  background-color: #409eff;
}
.el-aside {
}
.el-footer {
  padding: 0;
  height: 100%;
}
</style>
