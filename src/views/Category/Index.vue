<template>
    <el-container>
      <el-row>
        <div class="tag-group">
          <el-tag
            v-for="category in categoryList"
            :key="category.id"
            @click="redirect(category.title)"
            effect="light">
            {{ category.title }}
          </el-tag>
        </div>
      </el-row>
    </el-container>
</template>

<script>
import {
  mapActions,
  mapState
} from 'vuex'
export default {
  data () {
    return {}
  },
  methods: {
    ...mapActions(['getCategoryList']),
    redirect (title) {
      this.$router.push({name: 'CategoryList', query: { keyword: title, type: 'category' }})
    }
  },
  computed: {
    ...mapState(['categoryList'])
  },
  mounted () {
    this.getCategoryList()
  }
}
</script>

<style scoped>
.el-tag:nth-child(5n-4) {
  background-color: #409eff;
  border-color: #409eff;
}
.el-tag:nth-child(5n-3) {
  background-color: #67C23A;
  border-color: #67C23A;
}
.el-tag:nth-child(5n-2) {
  background-color: #909399;
  border-color: #909399;
}
.el-tag:nth-child(5n-1) {
  background-color: #F56C6C;
  border-color: #F56C6C;
}
.el-tag:nth-child(5n) {
  background-color: #E6A23C;
  border-color: #E6A23C;
}
.el-tag {
  margin-left: 10px;
  margin-top: 5px;
  color: #FFFFFF;
}
</style>
