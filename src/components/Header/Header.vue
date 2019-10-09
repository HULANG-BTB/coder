<template>
  <div class="header">
    <div class="logo">
      <div class="img"></div>
      <div class="title">Lazy OJ</div>
    </div>
    <div class="nav">
      <el-menu class="el-menu-demo" mode="horizontal" background-color="#409EFF" text-color="#fff">
        <el-submenu index="1">
          <template slot="title">
            <i class="el-icon-s-promotion"></i>
            <span>消息</span>
          </template>
          <el-menu-item index="1-1">没有新消息</el-menu-item>
        </el-submenu>
        <el-menu-item index="2" @click="loginDialogVisible = true" v-if="!loginStatus.username">
          <a>登录</a>
        </el-menu-item>
        <el-menu-item index="3" @click="registerDialogVisible = true" v-if="!loginStatus.username">
          <a>注册</a>
        </el-menu-item>
        <!--    登陆后显示    -->
        <el-submenu index="2" v-if="loginStatus.username">
          <template slot="title">
            <el-avatar :size="30" src="https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png"></el-avatar>
            <a>{{ loginStatus.username }}</a>
          </template>
          <el-menu-item index="2-1">个人中心</el-menu-item>
          <el-menu-item index="2-2" @click="logoutSubmit">注销登录</el-menu-item>
        </el-submenu>
      </el-menu>
    </div>
    <el-dialog
      title="登录"
      :visible.sync="loginDialogVisible"
      width="30%"
      center>
      <el-form :model="loginForm" label-width="100px">
        <el-form-item label="用户名">
          <el-input v-model="loginForm.username" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="密码">
          <el-input v-model="loginForm.password" autocomplete="off" type="password"></el-input>
        </el-form-item>
        <el-form-item label="验证码">
          <el-input v-model="loginForm.captcha">
            <template slot="append"><img src="http://lazyoj.cn/api/login/captchaCode" alt="" height="34px" @click="getCaptcha"></template>
          </el-input>
        </el-form-item>
      </el-form>
      <span slot="footer" class="dialog-footer">
        <el-button type="primary" @click="loginSubmit">登 录</el-button>
        <el-button @click="loginDialogVisible = false">取 消</el-button>
      </span>
    </el-dialog>
    <el-dialog
      title="注册"
      :visible.sync="registerDialogVisible"
      width="30%"
      center>
      <span>这是一段信息</span>
      <span slot="footer" class="dialog-footer">
        <el-button type="primary" @click="registerDialogVisible = false">登 录</el-button>
        <el-button @click="registerDialogVisible = false">取 消</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import {
  mapState,
  mapActions
} from 'vuex'
import {
  reqLoginSubmit,
  reqLogoutSubmit
} from '../../api'
export default {
  data () {
    return {
      loginDialogVisible: false,
      registerDialogVisible: false,
      loginForm: {
        username: '',
        password: '',
        captcha: ''
      }
    }
  },
  computed: {
    ...mapState(['userInfo']),
    loginStatus () {
      return this.userInfo
    }
  },
  methods: {
    ...mapActions(['getUserInfo']),
    async loginSubmit () {
      // this.loginDialogVisible = false
      const result = await reqLoginSubmit({username: this.loginForm.username, password: this.loginForm.password, captcha: this.loginForm.captcha})
      if (result.code === 1) {
        this.$message('登录成功')
        this.loginDialogVisible = false
        this.getUserInfo()
      }
    },
    async logoutSubmit () {
      const result = await reqLogoutSubmit()
      if (result.code === 1) {
        this.$message('注销成功')
        this.getUserInfo()
        this.$router.refresh()
      }
    },
    getCaptcha (event) {
      event.target.src = 'http://lazyoj.cn/api/login/captchaCode?t=' + Math.random()
    }
  }
}
</script>

<style scoped>
.header > .logo {
  padding-top: 10px;
  padding-left: 10px;
  float: left;
}
.header > .logo .img {
  width: 30px;
  height: 30px;
  float: left;
}
.header > .logo .title {
  font-family: "MV Boli";
  font-size: 24px;
  float: left;
}
.header > .nav {
  float: right;
}
.header i {
  color: black;
}
</style>
