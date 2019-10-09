<template>
  <div id="app">
    <el-container>
      <el-header>
        <Header></Header>
      </el-header>
      <el-container :style="{height: height+'px'}">
        <el-aside>
          <Aside></Aside>
        </el-aside>
        <el-main>
          <router-view></router-view>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>

<script>
import Header from './components/Header/Header'
import Aside from './components/Aside/Aside'
import {
  mapActions,
  mapState
} from 'vuex'
export default {
  name: 'App',
  components: {
    Header,
    Aside
  },
  computed: {
    ...mapState(['userInfo'])
  },
  mounted () {
    this.height = document.documentElement.clientHeight - 60
    this.getUserInfo()
  },
  methods: {
    ...mapActions(['getUserInfo'])
  },
  data () {
    return {
      height: 500
    }
  }
}
</script>

<style scoped>
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
  border-right: solid 1px #e6e6e6;
}
</style>
